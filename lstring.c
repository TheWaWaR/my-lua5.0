/*
** $Id: lstring.c,v 1.78 2002/12/04 17:38:31 roberto Exp $
** String table (keeps all strings handled by Lua)
** See Copyright Notice in lua.h
*/


#include <string.h>

#define lstring_c

#include "lua.h"

#include "lmem.h"
#include "lobject.h"
#include "lstate.h"
#include "lstring.h"



/* (weet:
 * 如果字符串哈稀表为空则释放相应内存, 几乎不会出现吧?...)
 * */
void luaS_freeall (lua_State *L) {
  lua_assert(G(L)->strt.nuse==0);
  luaM_freearray(L, G(L)->strt.hash, G(L)->strt.size, TString *);
}


/* (weet:
 * 1. 申请内存供新表使用
 * 2. 对原哈稀表的所有对象重新映射到新表
 * 3. 释放原表内存并更新 stringtable 相关字段)
 * */
void luaS_resize (lua_State *L, int newsize) {
  GCObject **newhash = luaM_newvector(L, newsize, GCObject *);
  stringtable *tb = &G(L)->strt;
  int i;
  for (i=0; i<newsize; i++) newhash[i] = NULL;
  /* rehash */
  for (i=0; i<tb->size; i++) {
    GCObject *p = tb->hash[i];
    while (p) {  /* for each node in the list */
      GCObject *next = p->gch.next;  /* save next */
      lu_hash h = gcotots(p)->tsv.hash;
      int h1 = lmod(h, newsize);  /* new position */
      lua_assert(cast(int, h%newsize) == lmod(h, newsize));
      p->gch.next = newhash[h1];  /* chain it */
      newhash[h1] = p;
      p = next;
    }
  }
  luaM_freearray(L, tb->hash, tb->size, TString *);
  tb->size = newsize;
  tb->hash = newhash;
}


/* (weet: 
 * 1. 分配内存
 * 2. 填充数据结构
 * 3. 添加到全局的字符串哈稀表中
 * */
static TString *newlstr (lua_State *L, const char *str, size_t l, lu_hash h) {
  TString *ts = cast(TString *, luaM_malloc(L, sizestring(l)));
  stringtable *tb;
  ts->tsv.len = l;
  ts->tsv.hash = h;
  ts->tsv.marked = 0;
  ts->tsv.tt = LUA_TSTRING;
  ts->tsv.reserved = 0;
  memcpy(ts+1, str, l*sizeof(char));
  ((char *)(ts+1))[l] = '\0';  /* ending 0 */
  tb = &G(L)->strt;
  h = lmod(h, tb->size);
  ts->tsv.next = tb->hash[h];  /* chain new entry */
  tb->hash[h] = valtogco(ts);
  tb->nuse++;
  if (tb->nuse > cast(ls_nstr, tb->size) && tb->size <= MAX_INT/2)
    luaS_resize(L, tb->size*2);  /* too crowded */
  return ts;
}


/* (weet:
 * 1. 计算字符串hash 
 * 2. 使用hash从stringtable中查找相应对象
 * 3. 如果找到即返回，找不到就创建一个新的)
 * */
TString *luaS_newlstr (lua_State *L, const char *str, size_t l) {
  GCObject *o;
  lu_hash h = (lu_hash)l;  /* seed */
  size_t step = (l>>5)+1;  /* if string is too long, don't hash all its chars */
  size_t l1;
  for (l1=l; l1>=step; l1-=step)  /* compute hash */
    h = h ^ ((h<<5)+(h>>2)+(unsigned char)(str[l1-1]));
  for (o = G(L)->strt.hash[lmod(h, G(L)->strt.size)];
       o != NULL;
       o = o->gch.next) {
    TString *ts = gcotots(o);
    if (ts->tsv.len == l && (memcmp(str, getstr(ts), l) == 0))
      return ts;
  }
  return newlstr(L, str, l, h);  /* not found */
}


Udata *luaS_newudata (lua_State *L, size_t s) {
  Udata *u;
  u = cast(Udata *, luaM_malloc(L, sizeudata(s)));
  u->uv.marked = (1<<1);  /* is not finalized */
  u->uv.tt = LUA_TUSERDATA;
  u->uv.len = s;
  u->uv.metatable = hvalue(defaultmeta(L));
  /* chain it on udata list */
  u->uv.next = G(L)->rootudata;
  G(L)->rootudata = valtogco(u);
  return u;
}


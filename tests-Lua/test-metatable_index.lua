
-- __add(a, b)                     for a + b
-- __sub(a, b)                     for a - b
-- __mul(a, b)                     for a * b
-- __div(a, b)                     for a / b
-- __mod(a, b)                     for a % b
-- __pow(a, b)                     for a ^ b
-- __unm(a)                        for -a
-- __concat(a, b)                  for a .. b
-- __len(a)                        for #a
-- __eq(a, b)                      for a == b
-- __lt(a, b)                      for a < b
-- __le(a, b)                      for a <= b
-- __index(a, b)  <fn or a table>  for a.b
-- __newindex(a, b, c)             for a.b = c
-- __call(a, ...)                  for a(...)



metafraction = {}
function metafraction.__index(tbl, key)
    print(key)
    for k, v in pairs(tbl) do print(k, v) end
    print '---'
    return key
end

t1 = {k1 = '1', k2 = '2'}
setmetatable(t1, metafraction)

print(t1.abc)

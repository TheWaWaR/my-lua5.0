
Dog = {className='TheDog'}

function Dog:new()
    obj = {sound = 'WangWangWangWang'}
    print("Before:print('----' .. 'bbb')")
    print('---')
    for k, v in pairs(self) do print(k, v) end
    print('self.className', self.className)
    print('=====')
    self.__index = self
    return setmetatable(obj, self)
end

function Dog:makeSound()
    print(self.sound)
    print('---')
    for k, v in pairs(self) do print(k, v) end
    print('self.className', self.className)
    print('---')
end

ww = Dog:new()
ww:makeSound()

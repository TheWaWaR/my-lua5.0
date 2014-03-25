
metafraction = {}
function metafraction.__add(f1, f2)
    print(type(f1), type(f2))
    sum = {}
    for i, v in pairs(f1) do 
        print('i:' , i)
        sum[i] = f1[i] + f2[i]
    end
    setmetatable(sum, metafraction)
    print('---')
    return sum
end

t1 = {1, 2, 3}
t2 = {10, 100, 1000}
setmetatable(t1, metafraction)
setmetatable(t2, metafraction)
s = t1 + t2
for k, v in pairs(s) do print(k, v) end
print('--------------')

s = s + s
for k, v in pairs(getmetatable(s)) do print(k, v) end
print('==------------')
for k, v in pairs(s) do print(k, v) end

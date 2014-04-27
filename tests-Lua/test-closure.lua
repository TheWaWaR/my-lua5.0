
function createCounter()
    local i = 0
    local function counter()
        i = i + 1
        print(i)
    end
    return counter
end

counter = createCounter()
print("counter:", counter)
for i = 1, 4 do
    print("i:", i)
    counter()
end

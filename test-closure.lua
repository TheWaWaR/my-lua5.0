

function createCounter()
    local i = 0
    local function counter()
        i = i + 1
        print(i)
    end
    return counter
end

counter1 = createCounter()
connter1()
connter1()
connter1()
connter1()

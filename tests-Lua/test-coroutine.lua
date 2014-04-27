

-- Simple productor & customer 
function productor()
    return coroutine.create(function (salt)
        local array = {1, 2, 3}
        for i = 1, 3 do -- lua 的数组下标是从 1 开始的
            print("p.i, p.array[i]:", i, array[i])
            --print("p.salt:", salt)
            salt = coroutine.yield(i, array[i]+salt)
        end
        print("p.dead")
        return -1, -1
    end)
end

function customer(prod)
    local salt = 10
    while true do
        --print("c.salt:", salt)
        local running, i, product = coroutine.resume(prod, salt)
        print("running, i, product:", running, i, product)
        salt = salt * 10
        if running then
            print(product)
        else
            break
        end
    end
end

customer(productor())



print("=======================================")

-- coroutine.wrap

function instream() 
    return coroutine.wrap(function ()
        while true do
            local line = io.stdin:read("*l")
            print("instream.line:", line)
            if line then
                coroutine.yield(line)
            else 
                print("EOF:", line)
                break
            end
        end
        print("instream.END")
    end)
end

function filter(ins) 
    return coroutine.wrap(function()
        while true do
            local line = ins()
            if line then 
                coroutine.yield("{" .. line .. "}")
            else 
                print("filter.END")
                break
            end
        end 
    end)
end

function outstream(ins) 
    while true do
        local line = ins()
        if line then
            print(line)
        else
            print("outstream.END")
            break
        end
    end
end

outstream(filter(instream()))



do
    print("-----------------------variadic arguments test")

    local function B(tab)
        print(tab.name .. " is " .. (tab.age or "unknown") .. " years old and likes " .. (tab.hobby or "nothing"))
    end

    local john = {name="john", hobby="golf", age="over 9000", comment="plays too much golf"}
    B(john)

    B({name = "tim"})
    B{name = "tim"}

    function head(x, ...)
        return x
    end

    x = head(1, 2, 3)
    print(x)

    function average(...)
        result = 0
        local arg = {...}
        for i, v in ipairs(arg) do
            result = result + v
        end
        return result / #arg
    end
    
    print("The average is", average(10, 5, 3, 4, 5, 6))
    
end

do
    print("-----------------------weak table test")

    local t1, t2, t3, t4 = {1}, {2}, {3}, {4} -- Create 4 tables
    local maintab = {t1, t2} -- Regular table, strong references to t1 and t2
    local weaktab = setmetatable({t1, t2, t3, t4}, {__mode = 'v'}) -- table with weak references.

    t1, t2, t3, t4 = nil, nil, nil, nil -- No more "strong" references to t3 and t4
    print(#maintab, #weaktab) --> 2 4

    collectgarbage() -- Destroy t3 and t4 and delete weak links to them.
    print(#maintab, #weaktab) --> 2 2
end


do
    print("-----------------------table test")

    fruits = {"banana", "orange", "apple"}
    print(table.concat(fruits, ","))
    
    table.remove(fruits)
    print(table.concat(fruits, ","))
    
    table.sort(fruits)
    print(table.concat(fruits, ","))
    
    mytable = setmetatable(
        {key1 = "value1"},
        {
            __index = function(mytable, key)
                if key == "key2" then
                    return "metatablevalue"
                else
                    return mytable[key]
                end
            end
        }
    )

    print(mytable.key1, mytable.key2)

    -- __newindex
    mymetatable = {}
    mytable = setmetatable({key1 = "value1"}, {__newindex = mymetatable})

    print(mytable.key1)

    mytable.newkey = "new value 2"
    print(mytable.newkey, mymetatable.newkey)

    mytable.key1 = "new  value 1"
    print(mytable.key1, mymetatable.newkey1)

    --[[
    You can see in the above program, if a key exists in the main table, it just updates it. 
    When a key is not available in the maintable, it adds that key to the metatable.
    --]]

    
    mytable =
        setmetatable(
        {key1 = "value1"},
        {
            __newindex = function(mytable, key, value)
                -- rawset sets value without using __newindex of metatable
                rawset(mytable, key, '"' .. value .. '"')
            end
        }
    )

    mytable.key1 = "new value"
    mytable.key2 = 4

    print(mytable.key1, mytable.key2)   
    
end

do
    print("-----------------------meta test")

    local meta = { } -- create a table for use as metatable

    -- a metatable can change the behaviour of many things
    -- here we modify the 'tostring' operation:
    -- this fields should be a function with one argument.
    -- it gets called with the respective object and should return a string
    meta.__tostring = function (object)
        return string.format("{ %d, %d }", object.x, object.y)
    end
    
    -- create an object
    local point = { x = 13, y = -2 }
    -- set the metatable
    setmetatable(point, meta)
    
    -- since 'print' calls 'tostring', we can use it directly:
    print(point) -- prints '{ 13, -2 }'
end    

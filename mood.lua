--mood.lua

--require("socket.core")
--require("LuaPanda").start("127.0.0.1",8818);

-- Get version information from host
major, minor, build = hostgetversion()
print( "The host version is ", major, minor, build)
print("The Lua interpreter version is ", _VERSION)

-- Define a function for host to call
function mood( b )

    -- return a mood conditional on parameter
    if (b and major > 0) then
        return 'mood-happy'
    elseif (major == 0) then
        return 'mood-confused'
    else
        return 'mood-sad'
    end
end

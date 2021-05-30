-- luabridge_test

printMessage("You can call C++ functions from Lua!")

function sumNumbers(a,b)
    printMessage("You can still call C++ functions from Lua functions!")
    return a + b
end


testString = "LuaBridge works!"
number = 42

window = {
    title = "Window v.0.1",
	size = {
        w = 400,
        h = 500
    },

    posx = 400,
    posy = 500
}


-- relative the vscode root directory
local current_folder = "src.lua."

-- Include the library.
local lovetoys = require(current_folder .. 'lovetoys')

-- Initialize:
-- debug = true will enable library console logs
-- globals = true will register lovetoys classes in the global namespace
-- so you can access i.e. Entity() in addition to lovetoys.Entity()
lovetoys.initialize({globals = true, debug = true})


function v_print(name, ...)
    local s = name .. "("
    for i = 1, select('#', ...) do
        s = s .. " " .. tostring(select(i, ...))
    end

    s = s .. " )"

    print(s)
end

local love = {
    graphics = {
        setColor = function (r, g, b) v_print("setColor", r, g, b) end,
        circle = function(...) v_print("circle", ...) end, 
        rectangle = function(...) v_print("rectangle", ...) end
    }
}


function love.load()
    -- Define a Component class.
    local Position = Component.create("position", {"x", "y"}, {x = 0, y = 0})
    local Velocity = Component.create("velocity", {"vx", "vy"})

    -- Create and initialize a new Entity.
    -- Note we can access Entity() in the global
    -- namespace since we used globals = true in 
    -- the lovetoys initialization.
    local player = Entity()
    player:initialize()

    -- Add position and velocity components. We are passing custom default values.
    player:add(Position(150, 25))
    player:add(Velocity(100, 100))
    
    -- Create a System class as lovetoys.System subclass.
    local MoveSystem = class("MoveSystem", System)

    -- Define this System's requirements.
    function MoveSystem:requires()
        return {"position", "velocity"}
    end

    function MoveSystem:update(dt)
        for _, entity in pairs(self.targets) do
            local position = entity:get("position")
            local velocity = entity:get("velocity")
            position.x = position.x + velocity.vx * dt
            position.y = position.y + velocity.vy * dt
        end
    end

    -- Create a draw System.
    local DrawSystem = class("DrawSystem", System)

    -- Define this System requirements.
    function DrawSystem:requires()
        return {"position"}
    end

    function DrawSystem:draw()
        for _, entity in pairs(self.targets) do
            love.graphics.rectangle("fill", entity:get("position").x, entity:get("position").y, 10, 10)
        end
    end

    -- Finally, we setup an Engine.
    engine = Engine()
    engine:addEntity(player)

    -- Let's add the MoveSystem to the Engine. Its update() 
    -- method will be invoked within any Engine:update() call.
    engine:addSystem(MoveSystem())
    
    -- This will be a 'draw' System, so the
    -- Engine will call its draw method.
    engine:addSystem(DrawSystem(), "draw")
end

function love.update(dt)
    -- Will run each system with type == 'update'
    engine:update(dt)
end

function love.draw()
    -- Will invoke the draw() method on each system with type == 'draw'
    engine:draw()
end

love.load()

for i = 1, 10, 1 do 
    love.update(0.033)
    love.draw()
end

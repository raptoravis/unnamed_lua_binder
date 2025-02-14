-- relative the vscode root directory
local current_folder = "src.lua."

local ecs = require(current_folder .. "ecslib")

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

function position_component(x, y)
    local component = ecs.component.new("position")

    component.x = x
    component.y = y

    return component
end

function rectangle_component(width, height)
    local component = ecs.component.new("shape")

    component.w = width
    component.h = height

    return component
end

function circle_component(radius)
    local component = ecs.component.new("shape")

    component.r = radius

    return component
end

function simple_system()
    local system = ecs.system.new({ "position", "shape" })

    function system:update(dt, entity)
        local position = entity:get("position")
        local shape    = entity:get("shape")

        local speed = 10

        position.x = position.x + dt * speed;
        position.y = position.y + dt * speed;

    end

    function system:draw(entity)
        local position = entity:get("position")
        local shape    = entity:get("shape")

        if entity:get("player") then
            love.graphics.setColor(1, 0.5, 0.3)
        else
            love.graphics.setColor(1, 1, 1)
        end

        if shape.r then
            love.graphics.circle("fill", position.x, position.y, shape.r)
        elseif shape.w and shape.h then
            love.graphics.rectangle("fill", position.x, position.y, shape.w, shape.h)
        else
            assert(false, "Shape requires dimensions.")
        end
    end

    return system
end

function love.load()
    world = ecs.world.new()

    local player = world:create_entity()
    player:add_component(ecs.component.new("player"))
    player:add_component(position_component(10, 10))
    player:add_component(rectangle_component(2, 2))

    local monster = world:create_entity()
    monster:add_component(ecs.component.new("monster"))
    monster:add_component(position_component(-10, -10))
    monster:add_component(circle_component(3))

    -- world:add_entity(player)
    world:add_system(simple_system())
end

function love.update(dt)
    world:update(dt)
end

function love.draw()
    world:draw()
end


love.load()

for i = 1, 10, 1 do 
    love.update(0.033)
    love.draw()
end

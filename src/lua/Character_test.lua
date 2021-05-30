-- Character_test

--require("socket.core")
require("LuaPanda").start("127.0.0.1",8818);

player = Character.new("Hero", 100)
player:setHealth(80)
hp = player:getHealth()
name = player:getName()
print("Character name: "..name..", HP = "..hp)


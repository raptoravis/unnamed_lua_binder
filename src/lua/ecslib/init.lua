local current_folder = (...):gsub('%.init$', '') -- package

local ecs = {
	_VERSION = "1.0.0",
	_DESCRIPTION = 'Entity Component System',
	_URL         = 'http://github.com',
	_LICENSE     = [[
	MIT
  ]]
}

ecs.entity	  = require(current_folder .. ".core.entity")
ecs.component = require(current_folder .. ".core.component")
ecs.system	  = require(current_folder .. ".core.system")
ecs.world	  = require(current_folder .. ".core.world")

return ecs;
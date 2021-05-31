--Module declaration (mandatory, meta fields recommended)
local ecs = {
	_VERSION     = '1.0.0',
	_DESCRIPTION = 'entity component system',
	_URL         = 'http://github.com/',
	_LICENSE     = [[
	  ...
	]]	
}

-- Private functions (when needed)
-- local isMyMaster = function (name)
--   return name == 'kikito'
-- end

ecs.entity	  = require("lib.ecs-core.entity")
ecs.component = require("lib.ecs-core.component")
ecs.system	  = require("lib.ecs-core.system")
ecs.world	  = require("lib.ecs-core.world")

-- Metatable (when needed)
-- setmetatable(ecs, {__call = function(_, name) return ecs.greet(name) end})

return ecs;

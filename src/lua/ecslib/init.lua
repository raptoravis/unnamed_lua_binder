local current_folder = (...):gsub('%.init$', '') -- "my-package"

entity	  = require(current_folder .. ".ecs-core.entity")
component = require(current_folder .. ".ecs-core.component")
system	  = require(current_folder .. ".ecs-core.system")
world	  = require(current_folder .. ".ecs-core.world")

return {
	entity	  = entity,
	component = component,
	system	  = system,
	world	  = world
}

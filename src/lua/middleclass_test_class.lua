-- relative the vscode root directory
local current_folder = "src.lua."

-- File 'middleclass_test_class.lua'
local class = require(current_folder .. 'lovetoys.lib.middleclass')

middleclass_test_class = class('middleclass_test_class')

local _internalClassCounter = 0

function middleclass_test_class:initialize()
  _internalClassCounter = _internalClassCounter + 1
  self.publicStuff = 2
end

function middleclass_test_class:getCount()
  return(_internalClassCounter)
end


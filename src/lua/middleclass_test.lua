-- relative the vscode root directory
local current_folder = "src.lua."

require(current_folder .. 'middleclass_test_class')

-- Try to change internal member...
_internalClassCounter = 4 -- Attempt to modify the _internalClassCounter variable

print(middleclass_test_class:getCount()) -- prints "0" .. 
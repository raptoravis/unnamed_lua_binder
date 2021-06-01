-- relative the vscode root directory
local current_folder = "src.lua."

require(current_folder .. 'middleclass_test_class')

-- Try to change internal member...
_internalClassCounter = 4 -- Attempt to modify the _internalClassCounter variable

print(middleclass_test_class:getCount()) -- prints "0" .. 

peter = middleclass_test_class:new('peter')
peter:shout() -- My name is peter and I have a secret. You will never know it!

-- print(_secretMethod(peter)) -- throws an error - _secretMethod is nil here.

stewie = middleclass_test_class:new('stewie', 2, 'male')

print(stewie:getName()) -- stewie
stewie.name = 'ann'
print(stewie.name) -- ann

print(stewie:getAge()) -- 2
stewie.age = 14        -- this isn't really modifying the age... it is creating a new public attribute called 'age'
-- the internal age is still unaltered
print(stewie:getAge()) -- 2
-- the newly created external age is also available.
print(stewie.age) -- 14

-- same goes with gender:

print(stewie:getGender()) -- 'male'
stewie.gender = 'female'
print(stewie:getGender()) -- 'male'
print(stewie.gender) -- 'female'

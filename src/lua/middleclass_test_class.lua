-- relative the vscode root directory
local current_folder = "src.lua."

-- File 'middleclass_test_class.lua'
local class = require(current_folder .. 'lovetoys.lib.middleclass')

middleclass_test_class = class('middleclass_test_class')

local _private = setmetatable({}, {__mode = "k"})   -- weak table storing all private attributes

local _internalClassCounter = 0

function middleclass_test_class:initialize(name, age, gender)
  _internalClassCounter = _internalClassCounter + 1
  self.name = name
  self.publicStuff = 2

  _private[self] = {
    age = age,
    gender = gender
  }
end

function middleclass_test_class:getCount()
  return(_internalClassCounter)
end

do
  local _secretMethod = function(self) -- notice the 'local' at the beginning, the = function and explicit self parameter
    return( 'My name is ' .. self.name .. ' and I have a secret.' )
  end

  function middleclass_test_class:shout()
    print( _secretMethod(self) .. ' You will never know it!' )
  end
end

local _secretClassMethod = function() -- self parameter out
  return( 'My name is ' .. MyClass3.name .. ' and I have a secret.' ) -- use MyClass3 directly.
end

function middleclass_test_class.classMethod(theClass)
  return( 'Being a public class named ' .. theClass.name .. ' is not a bad thing.' )
end

function middleclass_test_class:getName() -- shorter equivalent: MyClass4:getter('name')
  return self.name
end

function middleclass_test_class:getAge()
  return _private[self].age
end

function middleclass_test_class:getGender()
  return _private[self].gender
end


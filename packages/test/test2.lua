-- @Author: sxf
-- @Date:   2015-05-30 15:41:40
-- @Last Modified by:   sxf
-- @Last Modified time: 2015-05-31 13:12:24

local mylib = require "mylib"
for n in pairs(_ENV) do print(n) end

require "hello"
print "hello lua"
l_hello()
a, b = displayLuaFunction(2, 3.141592, 'hola')


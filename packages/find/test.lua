-- @Author: sxf
-- @Date:   2015-05-30 15:41:40
-- @Last Modified by:   sxf
-- @Last Modified time: 2015-05-31 14:43:50


local find = {} 
function find.hello()
	print("lua command: hello")
end
_ENV.find = find

function hello2()
	print("lua command: hello2")
end
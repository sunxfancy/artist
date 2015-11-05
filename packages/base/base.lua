-- @Author: sxf
-- @Date:   2015-06-03 21:04:27
-- @Last Modified by:   sxf
-- @Last Modified time: 2015-06-08 16:56:34

local base_tool_select = {}

function base_tool_select.onclick( x, y )
	print(x,y)
end

function base_tool_select.onmove( x, y )
	print(x,y)
end

function base_tool_select.onrelease( x, y )
	print(x,y)
end

_ENV.base_tool_select = base_tool_select

print(base_tool_select.onclick)

artist.AddToolFromLua(
	"select-tool",
	"base_tool_select.onclick",
	"base_tool_select.onrelease",
	"base_tool_select.onmove" )


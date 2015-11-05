-- @Author: sxf
-- @Date:   2015-05-31 15:50:02
-- @Last Modified by:   sxf
-- @Last Modified time: 2015-09-02 13:19:29

print("Hello World")

local action_map = {
	new_file_action = "New File",
	open_file_action = "Open File",
	save_file_action = "Save File"
}

for i,v in pairs(action_map) do
	artist.gtkActionRunAction(i, v)
end

artist.AddSearchPath("packages")
artist.SearchPackages()

artist.ActiveTool("brush-bezier")

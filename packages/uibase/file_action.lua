-- @Author: sxf
-- @Date:   2015-05-30 15:41:40
-- @Last Modified by:   sxf
-- @Last Modified time: 2015-06-03 21:01:38

local FileAction = {} 

function FileAction.New()
	print("New File Dialog")
end

function FileAction.Save()
	print("Save Command")
end

function FileAction.SaveAs()
	print("SaveAs Dialog")
end

function FileAction.Open()
	print("Open File Dialog")
end

_ENV.FileAction = FileAction

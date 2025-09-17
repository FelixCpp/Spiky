project("Premake")
	kind("Utility")
	targetdir("%{wks.location}/build/bin/" .. OutputDir .. "/%{prj.name}")
	objdir("%{wks.location}/build/bin-int/" .. OutputDir .. "/%{prj.name}")

	files({
		"%{wks.location}/**/Build-*.lua",
	})

	postbuildmessage("Regenerating project files with Premake ...")
	postbuildcommands({
		"\"%{prj.location}bin/premake5\" %{ACTION} --file=\"%{wks.location}Build.lua\" --os=\"windows\""
	})
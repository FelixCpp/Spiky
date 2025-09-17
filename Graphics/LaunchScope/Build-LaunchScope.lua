project("LaunchScope")
	kind("StaticLib")
	language("C++")
	cppdialect("C++23")
	targetdir("%{wks.location}/build/bin/" .. OutputDir .. "/%{prj.name}")
	objdir("%{wks.location}/build/bin-int/" .. OutputDir .. "/%{prj.name}")

	files({
		"private/AppStartup.cpp",

		"public/AppStartup.ixx",
		"public/LaunchScope.ixx",
		"public/StartupTask.ixx",
	})

	filter("system:windows")
		systemversion("latest")
		

	filter("configurations:Debug")
		runtime("Debug")
		symbols("On")

	filter("configurations:Release")
		runtime("Release")
		optimize("On")
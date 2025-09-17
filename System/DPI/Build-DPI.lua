project("DPI")
	kind("StaticLib")
	language("C++")
	cppdialect("C++20")
	targetdir("%{wks.location}/build/bin/" .. OutputDir .. "/%{prj.name}")
	objdir("%{wks.location}/build/bin-int/" .. OutputDir .. "/%{prj.name}")
	
	files({
		"public/DPI.ixx",
		"public/DPI-DPIService.ixx",
	})

	filter("system:windows")
		systemversion("latest")
		defines({ "PLATFORM_WINDOWS" })
		files({
			"public/Win32/DPI-ShCoreDPIService.ixx",
			"public/Win32/DPI-User32DPIService.ixx",
			"private/Win32/DPI-ShCoreDPIService.cpp",
			"private/Win32/DPI-User32DPIService.cpp",
		})

	filter("configurations:Debug")
		runtime("Debug")
		symbols("On")

	filter("configurations:Release")
		runtime("Release")
		optimize("On")
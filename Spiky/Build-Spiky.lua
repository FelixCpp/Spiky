project("Spiky")
    kind("StaticLib")
    language("C++")
    cppdialect("C++23")
    targetdir("%{wks.location}/build/bin/" .. OutputDir .. "/%{prj.name}")
    objdir("%{wks.location}/build/bin-int/" .. OutputDir .. "/%{prj.name}")

    files({
        "internal/**.ixx",
        "internal/**.cpp",
        "private/**.ixx",
        "private/**.cpp",
        "public/**.ixx",
    })

    links({
        "Logging",
        "Startup",
        "Math",
        "Monitor",
    })

    filter("files:**.ixx")
        compileas("Module")

    filter("system:windows")
        systemversion("latest")
        links({ "d2d1", "d3d11", "dwrite", "windowscodecs" })

    filter("configurations:Debug")
        runtime("Debug")
        symbols("On")

    filter("configurations:Release")
        runtime("Release")
        optimize("On")
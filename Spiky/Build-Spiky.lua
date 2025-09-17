project("Spiky")
    kind("StaticLib")
    language("C++")
    cppdialect("C++23")
    targetdir("%{wks.location}/build/bin/" .. OutputDir .. "/%{prj.name}")
    objdir("%{wks.location}/build/bin-int/" .. OutputDir .. "/%{prj.name}")

    files({
        "public/**.ixx",
        "private/**.ixx",
        "private/**.cpp"
    })

    links({
        "Logging",
        "Math",
        "DPI",
        "Monitor",
    })

    filter("files:**.ixx")
        compileas("Module")

    filter("system:windows")
        systemversion("latest")

    filter("configurations:Debug")
        runtime("Debug")
        symbols("On")

    filter("configurations:Release")
        runtime("Release")
        optimize("On")
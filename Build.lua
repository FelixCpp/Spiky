workspace("Spike")
    architecture("x64")
    startproject("App")
    staticruntime("Off")
    configurations({
        "Debug",
        "Release"
    })

    flags({
        "MultiProcessorCompile",
    })

    OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    group("System")
        include("System/Monitor/Build-Monitor.lua")

    group("Utilities")
        include("Logging/Build-Logging.lua")
        include("Startup/Build-Startup.lua")
        include("Math/Build-Math.lua")
    
    group("Build-Tools")
        include("Premake/Build-Premake.lua")

    group("") -- Root group
        include("Spiky/Build-Spiky.lua")
        include("App/Build-App.lua")
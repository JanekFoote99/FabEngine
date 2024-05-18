workspace "fabEngine-Core"
    architecture "x64"
    startproject "FabEngine-Core"

    configurations
    {
        "Debug",
        "Release"    
    }

    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includeDir = {}
includeDir["GLFW"] = "external/glfw/include"
includeDir["gl3w"] = "external/gl3w/include"
includeDir["Glad"] = "external/Glad/include"
includeDir["ImGui"] = "external/imgui"
includeDir["glm"] = "external/glm"

group "Dependencies"
    include "fabEngine-Core/external/glfw"
    include "fabEngine-Core/external/Glad"
    include "fabEngine-Core/external/imgui"
group ""

include "fabEngine-Core"

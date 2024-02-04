project "FabEngine-Core"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    -- pchheader "glpch.h"
    -- pchsource "src/glpch.cpp"

    files
    {
        "src/**.cpp",
        "inc/**.h",
        "src/Core/**.cpp",
        "inc/Core/**.h",
        "shader/**.glsl",
        "external/glm/glm/**.hpp",
        "external/glm/glm/**.inl",
        "external/imgui/examples/imgui_impl_glfw.cpp",
        "external/imgui/examples/imgui_impl_opengl3.cpp",
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs
	{
		"inc",
        "inc/Core",
		"%{includeDir.GLFW}",
        "%{includeDir.gl3w}",
		"%{includeDir.Glad}",
		"%{includeDir.ImGui}",
        "%{includeDir.glm}",
	}

    libdirs
    {
        "%{includeDir.ImGui}/bin/Debug-windows-x86_64/ImGui/ImGui.lib"
    }

    links 
    {
        "glfw",
        "Glad",
        "imgui",
        "opengl32"
    }

    filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLCORE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GLCORE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GLCORE_RELEASE"
		runtime "Release"
		optimize "on"
project "FabEngine-Core"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    -- pchheader "glpch.h"
    -- pchsource "src/glpch.cpp"

    -- Helper function: add dear imgui source files into project
    function imgui_as_src(fs_path, project_path)
        if (project_path == nil) then project_path = fs_path; end;	        -- default to same virtual folder as the file system folder (in this project it would be ".." !)
        files { fs_path .. "/*.cpp", fs_path .. "/*.h" }
        includedirs { fs_path, fs_path .. "/examples" }
        vpaths { [project_path] = { fs_path .. "/*.*", fs_path .. "/misc/natvis/*.natvis" } }  -- add in a specific folder of the Visual Studio project
        filter { "toolset:msc*" }
            files { fs_path .. "/misc/natvis/*.natvis" }
        filter {}
    end

    imgui_as_src ("..", "imgui")

    files
    {
        "inc/**.h",
        "src/**.cpp",
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
		"src",
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
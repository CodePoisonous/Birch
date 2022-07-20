workspace "Birch"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directories)
IncludeDir = {}
IncludeDir["GLFW"] = "Birch/vendor/GLFW/include"
IncludeDir["Glad"] = "Birch/vendor/Glad/include"
IncludeDir["ImGui"] = "Birch/vendor/imgui"

include "Birch/vendor/GLFW"
include "Birch/vendor/Glad"
include "Birch/vendor/imgui"

project "Birch"
	location "Birch"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/" .. outputdir .. "/%{prj.name}")
	
	pchheader "bcpch.h"
	pchsource "Birch/src/bcpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_WINDOWS",
			"BC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "BC_RELESASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:Dist"
		defines "BC_DIST"
		buildoptions "/MD"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Birch/vendor/spdlog/include",
		"Birch/src"
	}

	links
	{
		"Birch"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "BC_RELESASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:Dist"
		defines "BC_DIST"
		buildoptions "/MD"
		symbols "On"
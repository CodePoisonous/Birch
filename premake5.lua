workspace "Birch"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["glm"] = "Birch/vendor/glm"
IncludeDir["stb_image"] = "Birch/vendor/stb_image"

include "Birch/vendor/GLFW"
include "Birch/vendor/Glad"
include "Birch/vendor/imgui"

project "Birch"
	location "Birch"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "bcpch.h"
	pchsource "Birch/src/bcpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_WINDOWS",
			"BC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BC_RELESASE"
		runtime "Debug"
		symbols "on"

	filter "configurations:Dist"
		defines "BC_DIST"
		runtime "Debug"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Birch/vendor/spdlog/include",
		"Birch/src",
		"Birch/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Birch"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BC_RELESASE"
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "BC_DIST"
		runtime "Release"
		symbols "on"
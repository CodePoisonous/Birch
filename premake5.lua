workspace "Birch"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Birch"
	location "Birch"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "10.0.17134.0"

		defines
		{
			"BC_PLATFORM_WINDOWS",
			"BC_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BC_RELESASE"
		symbols "On"

	filter "configurations:Dist"
		defines "BC_DIST"
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
		systemversion "10.0.17134.0"

		defines
		{
			"BC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BC_RELESASE"
		symbols "On"

	filter "configurations:Dist"
		defines "BC_DIST"
		symbols "On"
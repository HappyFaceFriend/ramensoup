--premake5.lua

workspace "Ramensoup"
	architecture "x64"

	configurations {"Debug", "Release"}
	platforms {"Win64"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Ramensoup"
	location "Ramensoup"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Ramensoup/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src"
		--%{prj.name}vendor/spdlog/include
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RS_RELEASE"
		runtime "Release"
		optimize "on"



project "Ramensoup-Editor"
	location "Ramensoup-Editor"
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
		"Ramensoup/src",
		"%{prj.name}/src"
	}

	links
	{
		"Ramensoup"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RS_RELEASE"
		runtime "Release"
		optimize "on"
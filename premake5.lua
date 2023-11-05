--premake5.lua

workspace "Ramensoup"
	architecture "x64"

	configurations {"Debug", "Release"}
	platforms {"Win64"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLFW"] = "Ramensoup/vendor/GLFW/include"
IncludeDirs["Glad"] = "Ramensoup/vendor/Glad/include"
IncludeDirs["ImGui"] = "Ramensoup/vendor/ImGui"
IncludeDirs["glm"] = "Ramensoup/vendor/glm"
IncludeDirs["stb_image"] = "Ramensoup/vendor/stb_image"
IncludeDirs["assimp"] = "Ramensoup/vendor/assimp/include"

include "Ramensoup/vendor/assimp"

include "Ramensoup/vendor/GLFW"
include "Ramensoup/vendor/Glad"
include "Ramensoup/vendor/ImGui"

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
	}
	
	removefiles 
	{
		"%{prj.name}/src/Platform/Windows/*.h",
		"%{prj.name}/src/Platform/Windows/*.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.Glad}",
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.stb_image}",
		"%{IncludeDirs.assimp}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"assimp",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RS_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}
		files
		{
			"%{prj.name}/src/Platform/Windows/*.h",
			"%{prj.name}/src/Platform/Windows/*.cpp"
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
		"%{prj.name}/src",

		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.assimp}",
		"Ramensoup/vendor/spdlog/include",
	}

	links
	{
		"Ramensoup",
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
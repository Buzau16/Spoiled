workspace "Spoiled"
	architecture "x64"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Spyen"
	location "Spyen"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "spypch.h"
	pchsource "Spyen/src/spypch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"Spyen/src",
		"%{prj.name}/vendor/glew/include",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/vendor/glfw/include"

	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"
		
		defines {
			"SP_PLATFORM_WINDOWS",
			"SP_GL"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Spoiled")
		}
		
	filter "configurations:Debug"
		defines "SP_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "SP_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "SP_DIST"
		optimize "On"

project "Spoiled"
	location "Spoiled"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"Spyen/src",
		"Spyen/vendor/glew/include",
		"Spyen/vendor/glew",
		"Spyen/vendor/glfw/include"
	}

	libdirs{
		"Spyen/vendor/glew/lib/Release/x64",
		"Spyen/vendor/glfw/lib"
	}
	
	links {
		"Spyen",
		"glew32",
		"glfw3",
		"opengl32",
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"
		
		defines {
			"SP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SP_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "SP_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "SP_DIST"
		optimize "On"
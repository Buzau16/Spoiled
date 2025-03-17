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
	pchsource "Spyen/src/Spyen/spypch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"Spyen/src/Spyen",
		"%{prj.name}/vendor/GLEW/include;",
		"%{prj.name}/vendor/GLM;",
		"%{prj.name}/vendor/SDL/include;"

	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"SP_PLATFORM_WINDOWS"
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
		"Spyen/vendor/GLEW/include",
		"Spyen/vendor/GLM",
		"Spyen/vendor/SDL/include"
	}

	libdirs{
		"Spyen/vendor/GLEW/lib/Release/x64",
		"Spyen/vendor/SDL/lib"
	}
	
	links {
		"Spyen",
		"opengl32",
		"glew32",
		"SDL2",
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
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
		
	filter "system:windows"
		systemversion "latest"
		
		defines {
			"SP_PLATFORM_WINDOWS"
		}
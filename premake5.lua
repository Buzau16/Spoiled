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
	characterset "Unicode"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "spypch.h"
	pchsource "Spyen/src/spypch.cpp"

    flags { "MultiProcessorCompile" }
    buildoptions { "/utf-8" }
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/**.hpp"
	}
	
	includedirs {
		"Spyen/src",
		"%{prj.name}/vendor/glew/include",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/vendor/glfw/include",
		"%{prj.name}/vendor/spdlog/include"
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
		runtime "Debug"
		symbols "On"

		
	filter "configurations:Release"
		defines "SP_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "SP_DIST"
		runtime "Release"
		optimize "On"

project "Spoiled"
	location "Spoiled"
	kind "ConsoleApp"
	language "C++"
	characterset "Unicode"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	flags { "MultiProcessorCompile" }
    buildoptions { "/utf-8" }

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"Spyen/src",
		"Spyen/vendor/glew/include",
		"Spyen/vendor/glm",
		"Spyen/vendor/glfw/include",
		"Spyen/vendor/spdlog/include"
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
		runtime "Debug"
		symbols "On"
		linkoptions { "/NODEFAULTLIB:MSVCRT" }
		
	filter "configurations:Release"
		defines "SP_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "SP_DIST"
		runtime "Release"
		optimize "On"
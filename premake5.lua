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
	kind "SharedLib"
	language "C++"
	characterset "Unicode"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "spypch.h"
	pchsource "Spyen/src/spypch.cpp"

    flags { "MultiProcessorCompile" }
    buildoptions { "/utf-8" }
	
	files {
		"%{prj.name}/include/**.h",
		"%{prj.name}/include/**.cpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/vendor/glm/**.hpp"
	}
	
	includedirs {
		"Spyen/include",
		"Spyen/src",
		"%{prj.name}/vendor/glew/include",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/vendor/glfw/include",
		"%{prj.name}/vendor/spdlog/include"
	}


	libdirs{
		"%{prj.name}/vendor/glew/lib/Release/x64",
		"%{prj.name}/vendor/glfw/lib"
	}
	
	links {
		"glew32",
		"glfw3",
		"opengl32"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"
		
		
		defines {
			"SP_PLATFORM_WINDOWS",
			"SP_GL",
			"SPYEN_DLL_BUILD"
		}

		postbuildcommands{
			("{MKDIR} ../bin/" .. outputdir .. "/Spyen/bin"),
			("{MKDIR} ../bin/" .. outputdir .. "/Spyen/lib"),

			("{COPYDIR} %{prj.location}/include ../bin/" .. outputdir .. "/Spyen/include"),
			("{COPYDIR} %{prj.location}/shaders ../bin/" .. outputdir .. "/Spyen/shaders"),
			("{COPYDIR} %{prj.location}/bin ../bin/" .. outputdir .. "/Spyen/bin"),

			("{COPYDIR} %{prj.location}/vendor/glm/ ../bin/" .. outputdir .. "/Spyen/include"),
			("{COPYDIR} %{prj.location}/vendor/spdlog/include/ ../bin/" .. outputdir .. "/Spyen/include"),
			
			("{MOVE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Spyen/bin"),
			("{MOVE} ../bin/" .. outputdir .. "/Spyen/Spyen.lib ../bin/" .. outputdir .. "/Spyen/lib")
		}
		
	filter "configurations:Debug"
		defines "SP_DEBUG"
		runtime "Debug"
		symbols "On"
		includedirs{
			"%{prj.name}/vendor/vld/include"
		}
		libdirs{
			"%{prj.name}/vendor/vld/lib/Win64"
		}
		links{
			"vld"
		}

		
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


	prebuildcommands{
		("{COPYDIR} ../bin/" .. outputdir .. "/Spyen/ %{prj.location}/dependencies/spyen"),
		("{COPYFILE} ../bin/" .. outputdir .. "/Spyen/bin/Spyen.dll %{prj.location}")
	}

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"Spoiled/dependencies/spyen/include"
	}

	libdirs{
		"Spoiled/dependencies/spyen/lib"
	}
	
	links {
		"Spyen.lib"
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
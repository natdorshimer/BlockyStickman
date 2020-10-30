workspace "BlockyStickman"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}

project "BlockyStickman"
    location "BlockyStickman"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "blocky-pch.h"
    pchsource "%{prj.name}/src/Engine/blocky-pch.cpp"


    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/fmt/**.h",
        "%{prj.name}/vendor/fmt/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src/",
        "%{prj.name}/src/**",
        "%{prj.name}/src/Game/**",
        "%{prj.name}/vendor/SFML/include",
        "%{prj.name}/vendor/fmt/include",
        "%{prj.name}/vendor/entt/single_include",
    }

    
    defines
    {
        "FMT_HEADER_ONLY"
    }

    cppdialect "C++17"

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        libdirs 
        { 
            "%{prj.name}/vendor/SFML/vs2019/lib"
        }

        prebuildcommands
        {
            "{COPY} vendor/SFML/vs2019/bin/ ../bin/" .. outputdir .. "/%{prj.name}/",
            "{COPY} resources/ ../bin/" .. outputdir .. "/%{prj.name}/resources"
        }

        includedirs
        {
            "%{prj.name}/vendor/SFML/vs2019/include"
        }

    filter "system:linux"
   	staticruntime "On"
        systemversion "latest"
        
        linkoptions { '-Wl,-rpath=\\$$ORIGIN/lib' }
        
        libdirs 
        { 
            "%{prj.name}/vendor/SFML/GCC/lib/"
        }

        includedirs
        {
            "%{prj.name}/vendor/SFML/GCC/include",
        }

        prebuildcommands
        {
        	"mkdir -p ../bin/" .. outputdir .. "/%{prj.name}/",
            "{COPY} vendor/SFML/GCC/lib/ ../bin/" .. outputdir .. "/%{prj.name}/",
            "{COPY} resources/ ../bin/" .. outputdir .. "/%{prj.name}/"
        }
        


    filter "configurations:Debug"
        defines "BLKY_DEBUG"
        symbols "On"

        links
        {
            "sfml-graphics",
            "sfml-window",
            "sfml-system",
            "sfml-audio"
        }

    filter "configurations:Release"
        defines "BLKY_RELEASE"
        optimize "On"

        links
        {
            "sfml-graphics",
            "sfml-window",
            "sfml-system",
            "sfml-audio"
        }


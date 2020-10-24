workspace "BlockyStickman"
    architecture "x86"

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
        "%{prj.name}/vendor/SFML/include",
        "%{prj.name}/vendor/fmt/include",
        "%{prj.name}/vendor/entt/single_include",

    }

    libdirs 
    { 
        "%{prj.name}/vendor/SFML/lib"
    }

    prebuildcommands
    {
        "{COPY} vendor/SFML/bin/ ../bin/" .. outputdir .. "/%{prj.name}/"
    }
    
    defines
    {
        "FMT_HEADER_ONLY"
    }

    cppdialect "C++17"

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

    filter "system:linux"


    filter "system:Mac"
    
    filter "configurations:Debug"
        defines "BLKY_DEBUG"
        symbols "On"

        links
        {
            "sfml-graphics-d",
            "sfml-window-d",
            "sfml-system-d",
            "sfml-audio-d"
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


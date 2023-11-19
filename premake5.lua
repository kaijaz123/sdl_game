workspace "workspace"
    architecture "arm64"

    configurations {
        "Debug",
        "Release"
    }


project "game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/arm64/")
    objdir ("bin-int/arm64/")

    files
    {
        "game/src/**.h",
        "game/src/**.cpp"
    }

    includedirs --include the all the source code of library
    {
        "game/vendor/spdlog/include",
        "game/vendor/sdl2/include",
        "game/vendor/sdl_image/",
        "game/vendor/SDL_ttf/include/SDL3_ttf"
    }

    linkoptions --linkoptions (past to linker so it knows where to link to the path, frameworks path) 
    -- note: its equal to the args -F
    {
        "-F /System/Library/Frameworks",
        "-F /Library/Frameworks"
    }

    links --links (the actual project or library/framework name from either libdirs or linkoptions) 
    -- note: on mac its equal to the args -framework
    -- note: on windows its equal to the args -l
    {
        "SDL2.framework",
        "SDL2_image.framework",
        "SDL2_ttf.framework",
        "OpenGL.framework",
        "Cocoa.framework",
        "IOKit.framework",
        "CoreVideo.framework",
        "CoreFoundation.framework"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        symbols "off"
        optimize "on"
    
    -- note : on windows remember to copy and paste the dll file to the exact same path of the exe path



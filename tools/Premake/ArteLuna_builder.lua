workspace "ArteLuna"
    configurations { "Debug", "Release"}
    location "../../ArteLuna"
project "Game"
    dependson {"ArteLuna"}
    architecture "x64"
    location "../../ArteLuna/Game"
    debugdir "../../bin/Debug"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "../../bin/%{cfg.buildcfg}"
    includedirs { 
        "../../deps/arteluna/deps/glfw-3.3.8/include",
        "../../include",
        "../../deps/arteluna/include",
        "../../deps/arteluna/deps/glad2/include",
        "../../deps/arteluna/deps/imgui",
        "../../deps/arteluna/deps/tinyobjloader",
        "../../deps/arteluna/deps/glm/",
        "../../deps/arteluna/deps/stb/"
    }

    files {
        "../../src/**.cc", 
        "../../src/**.cpp", 
        "../../include/**.h"
    }
    libdirs {
        "../../deps/arteluna/bin/Debug",
        "../../deps/arteluna/bin/Release"
    }
    links {
        "ArteLuna.lib"
    }

    filter {"configurations:Release"}
    defines { "NDEBUG" }
    optimize "Speed"
    filter {"configurations:Debug"}
    defines { "DEBUG" }
    symbols "On"

    filter {}

project "ArteLuna"
    dependson {"glad2","mathlib","imgui", "tinyobjloader","soloud"}
    architecture "x64"
    location "../../ArteLuna/ArteLuna"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../../deps/arteluna/bin/%{cfg.buildcfg}"
    -- ignoredefaultlibraries { "MSVCRT" }
    includedirs { 
        "../../deps/arteluna/deps/glfw-3.3.8/include",
        "../../deps/arteluna/include",
        "../../deps/arteluna/deps/glad2/include",
        -- "../../deps/arteluna/deps/mathlib/include",
        "../../deps/arteluna/deps/imgui",
        "../../deps/arteluna/deps/tinyobjloader",
        -- "../../deps/arteluna/deps/soloud/include",
        "../../deps/arteluna/deps/glm/",
        "../../deps/arteluna/deps/stb/"
    }

    files {
        "../../deps/arteluna/src/**.cc", 
        "../../deps/arteluna/src/**.cpp", 
        "../../deps/arteluna/include/**.h"
    }
    removefiles {
        -- "../../src/**main.cc", 
    }
    libdirs { 
        "../../deps/arteluna/deps/glfw-3.3.8/lib-vc2019",
        "../../deps/arteluna/deps/openal-1.1/libs/Win64",
        "../../deps/arteluna/bin/Debug",
        "../../deps/arteluna/bin/Release"
    }
    
    links {
        -- "soloud.lib",
        -- "tinyobjloader.lib",
        -- "mathlib.lib",
        -- "OpenAL32.lib",
        "imgui.lib",
        "glad2.lib",
        "opengl32.lib",
        "glfw3.lib",
        "kernel32.lib",
        "user32.lib",
        "gdi32.lib",
        "winspool.lib",
        "comdlg32.lib",
        "advapi32.lib",
        "shell32.lib",
        "ole32.lib",
        "oleaut32.lib",
        "uuid.lib",
        "odbc32.lib",
        "odbccp32.lib"
    }
    filter {"configurations:Debug"}
        defines { "DEBUG" }
        symbols "On"

    filter {"configurations:Release"}
        defines { "NDEBUG" }
        optimize "Speed"



project "glad2"
    architecture "x64"
    location "../../ArteLuna/glad2"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../../deps/arteluna/bin/%{cfg.buildcfg}"

    includedirs {
        "../../deps/arteluna/deps/glad2/include"
    }

    files {
        "../../deps/arteluna/deps/glad2/src/gl.c", 
        "../../deps/arteluna/deps/glad2/include/glad/gl.h"
    }

-- project "mathlib"
--     architecture "x64"
--     location "../../ArteLuna/mathlib"
--     kind "StaticLib"
--     language "C++"
--     cppdialect "C++17"
--     targetdir "../../deps/arteluna/bin/%{cfg.buildcfg}"

--     includedirs {
--         "../../deps/arteluna/deps/mathlib/include"
--     }

--     files {
--         "../../deps/arteluna/deps/mathlib/src/*.cc", 
--         "../../deps/arteluna/deps/mathlib/include/*.h"
--     }

project "imgui"
    architecture "x64"
    location "../../ArteLuna/imgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../../deps/arteluna/bin/%{cfg.buildcfg}"

    includedirs {
        "../../deps/arteluna/deps/imgui",
        "../../deps/arteluna/deps/glfw-3.3.8/include",
    }

    files {
        "../../deps/arteluna/deps/imgui/*.cpp",
        "../../deps/arteluna/deps/imgui/*.h",
        "../../deps/arteluna/deps/imgui/backends/imgui_impl_glfw.h",
        "../../deps/arteluna/deps/imgui/backends/imgui_impl_glfw.cpp",
        "../../deps/arteluna/deps/imgui/backends/imgui_impl_opengl3.h",
        "../../deps/arteluna/deps/imgui/backends/imgui_impl_opengl3.cpp",
    }
    
    -- https://decovar.dev/blog/2019/08/04/glfw-dear-imgui/

-- project "tinyobjloader"
--     architecture "x64"
--     location "../../ArteLuna/tinyobjloader"
--     kind "StaticLib"
--     language "C++"
--     cppdialect "C++17"
--     targetdir "../../deps/arteluna/bin/%{cfg.buildcfg}"

--     includedirs {
--         "../../deps/arteluna/deps/tinyobjloader",
--     }

--     files {
--         "../../deps/arteluna/deps/tinyobjloader/*.cc",
--         "../../deps/arteluna/deps/tinyobjloader/*.h",
--         }
    
-- project "soloud"
--     architecture "x64"
--     location "../../ArteLuna/soloud"
--     kind "StaticLib"
--     language "C++"
--     cppdialect "C++17"
--     targetdir "../../bin/%{cfg.buildcfg}"
-- 	defines {"WITH_WINMM"}
    
--     includedirs {
--         "../../deps/soloud/include",
--         "../../deps/soloud/backend/openal",
--         "../../deps/openal-1.1/include",
--     }
--     libdirs { 
--         "../../deps/openal-1.1/libs/Win64",
--     }

--     files {
--         "../../deps/soloud/src/backend/winmm/**.c",
--         "../../deps/soloud/src/backend/winmm/**.cpp",
--         "../../deps/soloud/src/audiosource/wav/**.c",
--         "../../deps/soloud/src/audiosource/wav/**.h",
--         "../../deps/soloud/src/audiosource/sfxr/*.c",
--         "../../deps/soloud/src/core/**.cpp",
--         "../../deps/soloud/include/**.h",
--     }

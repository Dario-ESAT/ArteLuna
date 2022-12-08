workspace "ArteLuna"
    configurations { "Debug", "Release"}
    location "../../ArteLuna"

project "ArteLuna"
    dependson {"glad2","mathlib","imgui", "tinyobjloader","soloud"}
    architecture "x64"
    location "../../ArteLuna/ArteLuna"
    debugdir "../../bin/Debug"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "../../bin/%{cfg.buildcfg}"

    includedirs { 
        "../../deps/glfw-3.3.8/include",
        "../../include",
        "../../deps/glad2/include",
        "../../deps/mathlib/include",
        "../../deps/imgui",
        "../../deps/tinyobjloader",
        "../../deps/soloud/include",
    }

    files {
        "../../src/**.cc", 
        "../../src/**.cpp", 
        "../../include/**.h"
    }
    
    libdirs { 
        "../../deps/glfw-3.3.8/lib-vc2019",
        "../../deps/openal-1.1/libs/Win64",
        "../../bin/Debug",
        "../../bin/Release"
    }
    
    links {
        "soloud.lib",
        "tinyobjloader.lib",
        "mathlib.lib",
        "OpenAL32.lib",
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
    targetdir "../../bin/%{cfg.buildcfg}"

    includedirs { 
        "../../deps/glad2/include"
    }

    files {
        "../../deps/glad2/src/gl.c", 
        "../../deps/glad2/include/glad/gl.h"
    }

project "mathlib"
    architecture "x64"
    location "../../ArteLuna/mathlib"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../../bin/%{cfg.buildcfg}"

    includedirs {
        "../../deps/mathlib/include"
    }

    files {
        "../../deps/mathlib/src/*.cc", 
        "../../deps/mathlib/include/*.h"
    }

project "imgui"
    architecture "x64"
    location "../../ArteLuna/imgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../../bin/%{cfg.buildcfg}"

    includedirs {
        "../../deps/imgui",
        "../../deps/glfw-3.3.8/include",
    }

    files {
        "../../deps/imgui/*.cpp",
        "../../deps/imgui/*.h",
        "../../deps/imgui/backends/imgui_impl_glfw.h",
        "../../deps/imgui/backends/imgui_impl_glfw.cpp",
        "../../deps/imgui/backends/imgui_impl_opengl3.h",
        "../../deps/imgui/backends/imgui_impl_opengl3.cpp",
    }
    


project "tinyobjloader"
    architecture "x64"
    location "../../ArteLuna/tinyobjloader"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../../bin/%{cfg.buildcfg}"

    includedirs {
        "../../deps/tinyobjloader",
    }

    files {
        "../../deps/tinyobjloader/*.cc",
        "../../deps/tinyobjloader/*.h",
        }
    
project "soloud"
    architecture "x64"
    location "../../ArteLuna/soloud"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../../bin/%{cfg.buildcfg}"

    includedirs {
        "../../deps/soloud/include",
        "../../deps/soloud/backend/openal",
    }

    files {
        "../../deps/soloud/src/**.cpp",
        "../../deps/soloud/src/**.c",
        "../../deps/soloud/include/**.h",
    }
    
    -- https://decovar.dev/blog/2019/08/04/glfw-dear-imgui/

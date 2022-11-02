workspace "ArteLuna"
    configurations { "Debug", "Release"}
    location "../../ArteLuna"

project "ArteLuna"
    dependson {"glad2","mathlib","imgui"}
    architecture "x64"
    location "../../ArteLuna/ArteLuna"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "../../bin/%{cfg.buildcfg}"

    includedirs { 
        "../../deps/glfw-3.3.8/include",
        "../../include",
        "../../deps/glad2/include",
        "../../deps/mathlib/include",
        "../../deps/imgui"
    }

    vpaths { 
        ["include"] = "**.h",
        ["src"] = {"**.cc, **.cpp"}
    }
    
    files {
        "../../src/**.cc", 
        "../../src/**.cpp", 
        "../../include/**.h"
    }

    links {
        "mathlib.lib",
        "imgui.lib",
        "glad2.lib",
        "opengl32.lib",
        "glfw3.lib",
        -- "glfw3dll.lib",
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
    
    libdirs { 
        "../../deps/glfw-3.3.8/lib-vc2019",
        "../../bin/Debug",
        "../../bin/Release"
    }
    filter {"configurations:Debug"}
        defines { "DEBUG" }
        symbols "On"

    filter {"configurations:Release"}
        defines { "NDEBUG" }
        optimize "On"



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

    vpaths { 
        ["include"] = "**.h",
        ["src"] = {"**.cc, **.cpp"}
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

    vpaths { 
        ["include"] = "**.h",
        ["src"] = {"**.cc, **.cpp"}
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

    vpaths { 
        ["include"] = "../../deps/imgui/**.h",
        ["include/backends"] = "../../deps/imgui/backends/**.h",
        ["src"] = {"../../deps/imgui/**.cc, ../../deps/imgui/**.cpp"},
        ["src/backends"] = "../../deps/imgui/backends/**.cpp",
    }
    
    files {
        "../../deps/imgui/*.cpp",
        "../../deps/imgui/*.h",
        "../../deps/imgui/backends/imgui_impl_glfw.h",
        "../../deps/imgui/backends/imgui_impl_glfw.cpp",
        "../../deps/imgui/backends/imgui_impl_opengl3.h",
        "../../deps/imgui/backends/imgui_impl_opengl3.cpp",
    } 

    -- https://decovar.dev/blog/2019/08/04/glfw-dear-imgui/
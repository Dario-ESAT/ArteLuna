workspace "ArteLuna"
    configurations { "Debug", "Release"}
    location "../../ArteLuna"

project "ArteLuna"
    dependson {"glad2"}
    architecture "x64"
    location "../../ArteLuna/ArteLuna"
    kind "ConsoleApp"
    language "C++"
    targetdir "../../bin/%{cfg.buildcfg}"

    -- Headers
    includedirs { 
        "../../deps/glfw-3.3.8/include",
        "../../include",
        "../../deps/glad2/include"
    }

    -- Source
    vpaths { 
        ["include"] = "**.h",
        ["src"] = {"**.cc, **.cpp"}
    }
    
    files {
        "../../src/*.cc", 
        "../../src/*.cpp", 
        "../../include/*.h"
    } 
    -- Linkado

    links { 
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
    -- Filter
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
    targetdir "../../bin/%{cfg.buildcfg}"

    includedirs { 
        "../../deps/glad2/include"
    }

    -- Source
    vpaths { 
        ["include"] = "**.h",
        ["src"] = {"**.cc, **.cpp"}
    }
    
    files {
        "../../deps/glad2/src/gl.c", 
        "../../deps/glad2/include/glad/gl.h"
    } 
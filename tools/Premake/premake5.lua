workspace "ArteLuna"
    configurations { "Debug", "Release"}
    location "../../ArteLuna"

project "ArteLuna"
    architecture "x64"
    location "../../ArteLuna/ArteLuna"
    kind "ConsoleApp"
    language "C++"
    targetdir "../../bin/"


    -- Headers

    includedirs { 
        "../../deps/GLFW/include",
        "../../include"
    }

    -- Source

    -- Linkeado

    links { 
        "opengl32.lib",
        "glfw3.lib",
        "glfw3dll.lib",
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
        "odbccp32.lib",
        "%(AdditionalDependencies)"
    }
    libdirs { "../../deps/GLFW/lib-vc2019" }

    -- Filtros
--[[ 
    filter "src"
    defines {"src"}
    files {"src/**.cpp"}

    filter "include"
    defines {"include"}
    files {"include/**.h"}

    filter "bin"
    defines {"bin"}
    files {"include/**.exe"}

    filter "deps"
    defines {"deps"}
    files {"deps/GLFW/include/**.h"}

    filter "tools"
    defines {"tools"}

    filter "examples"
    defines {"examples"}

    filter {} ]]
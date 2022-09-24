workspace "ArteLuna"
    configurations { "Debug", "Release"}
    location "../../ArteLuna"

project "ArteLuna"
    architecture "x64"
    location "../../ArteLuna/ArteLuna"
    kind "ConsoleApp"
    language "C++"
    targetdir "../../bin/%{cfg.buildcfg}"


    -- Headers

    includedirs { 
        "../../deps/GLFW/include",
        "../../include"
    }

    -- Source
    vpaths {
        ["include"] = "**.h",
        ["src"] = {"**.cc, **.cpp"}
    }
    -- Linkado

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
    libdirs { 
        "../../deps/GLFW/lib-vc2019"
    }

   
workspace "SoundEditor"
    configurations { "Debug", "Release"}
    location "../SoundEditor/SoundEditor"

project "SoundEditor"
    dependson {"imgui"}
    architecture "x64"
    location "../SoundEditor/SoundEditor/SoundEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "../SoundEditor/bin/%{cfg.buildcfg}"

    includedirs {
        "../../deps/imgui",
        "../../deps/imgui/backends/",
        "../SoundEditor/include",
        "../SoundEditor/deps/sdl2/include",
    }

    
    vpaths {
        ["include"] = "**.h",
        ["src"] = {"**.cc, **.cpp"}
    }
    
    files {
        "../SoundEditor/include/*.h",
        "../SoundEditor/src/*.cpp",
        "../SoundEditor/src/*.cc",
        "../SoundEditor/examples/imnode/SDL/include/*.h",
        "../../deps/imgui/backends/imgui_impl_opengl3.h",
        "../../deps/imgui/backends/imgui_impl_glfw.h",
    }
    
    libdirs {
        "../SoundEditor/bin/Debug",
        "../SoundEditor/bin/Release",
        "../SoundEditor/deps/sdl2/lib/x64",
    }

    links {
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

    filter { "configurations:Debug"}
    defines {"DEBUG"}
    symbols "On"

    filter { "configurations:Release"}
    defines {"NDEBUG"}
    symbols "On"


project "imgui"
    architecture "x64"
    location "../SoundEditor/SoundEditor/imgui"
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
        ["src"] = "../../deps/imgui/**.cc, ../../deps/imgui/**.cpp",
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
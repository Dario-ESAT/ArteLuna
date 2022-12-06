workspace "SoundEditor"
    configurations { "Debug", "Release"}
    location "../SoundEditor/SoundEditor"

project "SoundEditor"
    
    dependson {"imgui","glad2","soloud"}
    architecture "x64"
    location "../SoundEditor/SoundEditor/SoundEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "../SoundEditor/bin/%{cfg.buildcfg}"

    includedirs {
        "../../deps/glfw-3.3.8/include",
        "../../deps/glad2/include",
        "../../deps/imgui",
        "../../deps/miniaudio/include",
        "../SoundEditor/include",
        "../SoundEditor/deps/soloud/include",
        "../SoundEditor/deps/soloud/src/miniaudio"
    }
    
    files {
        "../SoundEditor/include/**.h",
        "../SoundEditor/src/**.cpp",
        "../SoundEditor/src/**.cc",
    }
    
    libdirs {
        "../../deps/glfw-3.3.8/lib-vc2019",
        "../SoundEditor/bin/Debug",
        "../SoundEditor/bin/Release",
    }
--   ignoredefaultlibraries { "MSVCRT" }
    links {
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

    -- filter "system:windows"
	-- 	systemversion "latest"

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
		staticruntime "Off"
        runtime "Release"
    
    filter "configurations:Release"
        defines {"NDEBUG"}
        runtime "Release"
        optimize "Speed"
		staticruntime "Off"
        filter {}

project "glad2"
    architecture "x64"
    location "../SoundEditor/SoundEditor/glad2"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../SoundEditor/bin/%{cfg.buildcfg}"

    includedirs { 
        "../../deps/glad2/include"
    }

    files {
        "../../deps/glad2/src/gl.c", 
        "../../deps/glad2/include/glad/gl.h"
    }

project "imgui"
    architecture "x64"
    location "../SoundEditor/SoundEditor/imgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../SoundEditor/bin/%{cfg.buildcfg}"

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

project "soloud"
    architecture "x64"
    location "../SoundEditor/SoundEditor/soloud"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../SoundEditor/bin/%{cfg.buildcfg}"

    includedirs {
        "../SoundEditor/deps/soloud/include",
        "../SoundEditor/deps/soloud/src/miniaudio"
    }

    files {
        "../SoundEditor/deps/soloud/**.cpp",
        "../SoundEditor/deps/soloud/**.h",
    }

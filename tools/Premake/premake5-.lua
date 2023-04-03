workspace "ArteLuna"
  configurations { "Debug", "Release"}
  location "../../ArteLuna"
  includedirs { 
    "../../deps/glfw-3.3.8/include",
    "../../include",
    "../../deps/glad2/include",
    "../../deps/imgui",
    "../../deps/tinyobjloader",
    "../../deps/glm/",
    "../../deps/stb/"
  }
  files {
    "../../src/**.cc", 
    "../../src/**.cpp", 
    "../../include/**.h"
  }

project "Game"
  architecture "x64"
  location "../../ArteLuna/Game"
  debugdir "../../bin/Debug"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  targetdir "../../bin/%{cfg.buildcfg}"
  files {
    "../../src/**.cc", 
    "../../src/**.cpp", 
    "../../include/**.h"
  }
  libdirs {
    "../../bin/Debug",
    "../../bin/Release"
  }
  links {
    "ArteLuna.lib"
  }
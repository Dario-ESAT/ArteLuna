#!lua
conan_build_type = "Release"
conan_arch = "x86_64"

conan_includedirs = {"C:/Users/riveralu/.conan/data/tinyobjloader/2.0.0-rc10/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include",
"C:/Users/riveralu/.conan/data/imgui/1.89.2/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include"}
conan_libdirs = {"C:/Users/riveralu/.conan/data/tinyobjloader/2.0.0-rc10/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/lib",
"C:/Users/riveralu/.conan/data/imgui/1.89.2/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/lib"}
conan_bindirs = {"C:/Users/riveralu/.conan/data/imgui/1.89.2/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/bin"}
conan_libs = {"tinyobjloader", "imgui"}
conan_system_libs = {"imm32"}
conan_defines = {}
conan_cxxflags = {}
conan_cflags = {}
conan_sharedlinkflags = {}
conan_exelinkflags = {}
conan_frameworks = {}

conan_includedirs_tinyobjloader = {"C:/Users/riveralu/.conan/data/tinyobjloader/2.0.0-rc10/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include"}
conan_libdirs_tinyobjloader = {"C:/Users/riveralu/.conan/data/tinyobjloader/2.0.0-rc10/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/lib"}
conan_bindirs_tinyobjloader = {}
conan_libs_tinyobjloader = {"tinyobjloader"}
conan_system_libs_tinyobjloader = {}
conan_defines_tinyobjloader = {}
conan_cxxflags_tinyobjloader = {}
conan_cflags_tinyobjloader = {}
conan_sharedlinkflags_tinyobjloader = {}
conan_exelinkflags_tinyobjloader = {}
conan_frameworks_tinyobjloader = {}
conan_rootpath_tinyobjloader = "C:/Users/riveralu/.conan/data/tinyobjloader/2.0.0-rc10/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab"

conan_includedirs_imgui = {"C:/Users/riveralu/.conan/data/imgui/1.89.2/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include"}
conan_libdirs_imgui = {"C:/Users/riveralu/.conan/data/imgui/1.89.2/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/lib"}
conan_bindirs_imgui = {"C:/Users/riveralu/.conan/data/imgui/1.89.2/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/bin"}
conan_libs_imgui = {"imgui"}
conan_system_libs_imgui = {"imm32"}
conan_defines_imgui = {}
conan_cxxflags_imgui = {}
conan_cflags_imgui = {}
conan_sharedlinkflags_imgui = {}
conan_exelinkflags_imgui = {}
conan_frameworks_imgui = {}
conan_rootpath_imgui = "C:/Users/riveralu/.conan/data/imgui/1.89.2/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab"

function conan_basic_setup()
    configurations{conan_build_type}
    architecture(conan_arch)
    includedirs{conan_includedirs}
    libdirs{conan_libdirs}
    links{conan_libs}
    links{conan_system_libs}
    links{conan_frameworks}
    defines{conan_defines}
    bindirs{conan_bindirs}
end

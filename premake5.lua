workspace "Zephyr"
    architecture "x64"

    configurations{
        "Debug",
        "Release",
        "Dist"
    }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "Zephyr"
    location "Zephyr"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

    pchheader "zppch.h"
    pchsource "Zephyr/src/zppch.cpp"

files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
    "%{prj.name}/src/**.c",
    "Zephyr/dependencies/include/**.h",
    
    "Zephyr/vendor/imgui/*.cpp",
    "Zephyr/vendor/imgui/*.h",
    
    -- ImGui backends for GLFW + OpenGL only
    "Zephyr/vendor/imgui/backends/imgui_impl_glfw.cpp",
    "Zephyr/vendor/imgui/backends/imgui_impl_opengl3.cpp",
    "Zephyr/vendor/imgui/backends/imgui_impl_glfw.h",
    "Zephyr/vendor/imgui/backends/imgui_impl_opengl3.h"
}
    includedirs {
        "Zephyr/vendor/imgui",
        "Zephyr/vendor/spdlog/include",
        "Zephyr/dependencies/include",
        "%{prj.name}/src",
        "%{prj.name}/include"
    }

    libdirs {
        "Zephyr/dependencies/lib"   -- <-- where glfw3.lib will go
    }

    links {
        "glfw3",         -- name of your lib (glfw3.lib)
        "opengl32.lib"   -- Windows OpenGL
    }


    filter "files:Zephyr/vendor/imgui/*.cpp"
        flags { "NoPCH" }

    filter {} 

    filter "files:Zephyr/vendor/imgui/backends/*.cpp"
        flags { "NoPCH" }

    filter {}

    filter "files:Zephyr/src/glad.c"
        flags { "NoPCH" }

    filter {}  



    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"   -- safer for DLLs
        systemversion "latest"

        defines {
            "ZP_PLATFORM_WINDOWS",
            "ZP_BUILD_DLL"
        }

        postbuildcommands {
            ("{MKDIR} ../bin/" .. outputDir .. "/Sandbox/"),
            ("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox/")
        }

    filter {"system:windows", "configurations:Release"}
        buildoptions "/utf-8"
        defines "ZP_RELEASE"
        optimize "On"

    filter {"system:windows", "configurations:Debug"}
        buildoptions "/utf-8"
        defines "ZP_DEBUG"
        symbols "On"

    filter {"system:windows", "configurations:Dist"}
        buildoptions "/utf-8"
        defines "ZP_DIST"
        optimize "On"



project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs {
        "Zephyr/vendor/spdlog/include",
        "Zephyr/vendor/imgui",
        "Zephyr/dependencies/include",
        "Zephyr/src",
        "Zephyr/include"
    }

    links {
        "Zephyr"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "ZP_PLATFORM_WINDOWS",
        }

    filter {"system:windows", "configurations:Release"}
        buildoptions "/utf-8"
        defines "ZP_RELEASE"
        optimize "On"

    filter {"system:windows", "configurations:Debug"}
        buildoptions "/utf-8"
        defines "ZP_DEBUG"
        symbols "On"

    filter {"system:windows", "configurations:Dist"}
        buildoptions "/utf-8"
        defines "ZP_DIST"
        optimize "On"

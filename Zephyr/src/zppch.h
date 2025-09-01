#pragma once

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <glad/glad.h>        // or whatever loader you use

#include <GLFW/glfw3.h>       // windowing system

// ImGui core
#include "imgui.h"

// ImGui backends
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <queue>


#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>




#ifdef ZP_PLATFORM_WINDOWS
	#include<Windows.h>
#endif


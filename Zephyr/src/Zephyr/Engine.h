#pragma once
#include "Core.h"
#include <GLFW/glfw3.h>
namespace Zephyr {


	class ZEPHYR_API Engine
	{
	public:
		void InitWindow(GLFWwindow*& window, int width, int height, const char* name);
		static void ErrorCallback(int error, const char* description);
    

	private:
		
	};

}
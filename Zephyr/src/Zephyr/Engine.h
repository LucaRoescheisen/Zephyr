#pragma once
#include "Core.h"
#include <GLFW/glfw3.h>
#include "Editor UI/EditorUI.h"
namespace Zephyr {


	class ZEPHYR_API Engine
	{
	public:
		void InitWindow(GLFWwindow*& window, int width, int height, const char* name);
		static void ErrorCallback(int error, const char* description);

		void OnMinimiseEvent(int isAppMinimised) {
			if (isAppMinimised) { ZP_CORE_TRACE("Application is minimised: Rendering Stopped"); }
			else { ZP_CORE_TRACE("Application is not minimised: Rendering Started"); }
			m_ShouldRender = isAppMinimised;
		}


	private:
		uint8_t m_ShouldRender = 1;

	};

}
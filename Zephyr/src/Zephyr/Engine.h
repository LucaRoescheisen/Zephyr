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
		void InitUI(GLFWwindow* window) {
			m_EditorUI.InitEditorUI(window);
		
		}
		void RenderUI() {
			m_EditorUI.RenderEditorUI();
		}

	private:
		EditorUI m_EditorUI;
	};

}
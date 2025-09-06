#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Engine.h"
#include "Log.h"
#include "Layer.h"
#include <GLFW/glfw3.h>


namespace Zephyr {

	class ZEPHYR_API Application
	{
	public:
		Application() {
			
		}
		void Run();
		void OnEvent(Event& e);
		void SetVSync(bool enabled) { 
			ZP_CORE_TRACE("VSync Enabled");
			m_VSync = enabled;
			glfwSwapInterval(enabled ? 1 : 0);
		}



	private:
		GLFWwindow* m_Window = nullptr;
		LayerStack m_LayerStack;
		Engine m_Engine;
		EditorUI m_EditorUI;
		bool m_VSync = true;
		bool m_Running = true;
		
		void SetGLFWCallbacks();

		//----------------------------------------------Event Handlers----------------------------------------------//


		void OnWindowClose(WindowClose& ev) {
			m_Running = false;
			glfwTerminate();
		}
	};

	// Defined in client
	Application* CreateApplication();




} 




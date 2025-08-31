#include "zppch.h"
#include "Application.h"
#include "Events/Event.h"
#include "Log.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "zppch.h"

namespace Zephyr {

	
	void Application::Run() {	
		m_Engine.InitWindow(m_Window, 1920, 1080, "Zephyr");
		glfwSetWindowUserPointer(m_Window, this);

		//Set glfwCallbacks
		SetGLFWCallbacks();
		m_LayerStack.PushOverlay(new WindowLayer(m_Window));





		while (m_Running) {
			//find deltatime

			//update input
			//update renderer

			//render

			glfwSwapBuffers(m_Window);
			glfwPollEvents();
			
		}
	}


	
	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {		//it is an iterator, that is an object that holds the address of the layer
			(*it)->OnEvent(e);															//dereference to find which layer/overlay then pass the event in
			if (e.IsHandled()) {	
				break;																	//If the event is handled we can exit
			}
		}																						//We travel to the next layer/overlay to see whether it can handle the event
																			
		
		//Special Case if the window closes: we want to avoid windowlayer from know application exists
		dispatcher.Dispatch<WindowClose>([this](WindowClose& ev) {
			ZP_CORE_TRACE(ev.ToString());
			m_Running = !ev.IsCloseRequested();			//Sets IsCLoseRquested to true, so we need to invert to turn off the program
			return true;
			});
	}



	void Application::SetGLFWCallbacks() {
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* win, int w, int h) {
			Application* app = static_cast<Application*>(glfwGetWindowUserPointer(win));
			app->OnEvent(WindowResize(w, h));  
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* win) {
			Application* app = static_cast<Application*>(glfwGetWindowUserPointer(win));
			app->OnEvent(WindowClose(true));
			});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* win, int focused) {
			Application* app = static_cast<Application*>(glfwGetWindowUserPointer(win));
			WindowFocus focusEvent(focused);  // create a named lvalue
			app->OnEvent(focusEvent);
			});
	}		





}
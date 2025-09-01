#include "zppch.h"
#include "Application.h"
#include "Events/Event.h"
#include "Log.h"

#include "zppch.h"

namespace Zephyr {
	#define SET_GLFW_CALLBACK(window, callbackFn, EventExpr)\
		callbackFn(window, [](GLFWwindow* win, auto... args){\
			Application* app = static_cast<Application*>(glfwGetWindowUserPointer(win)); \
			app->OnEvent(EventExpr(args...)); \
		});
	


	void Application::Run() {	
		m_Engine.InitWindow(m_Window, 1920, 1080, "Zephyr");
		m_Engine.InitUI(m_Window);
		glfwSetWindowUserPointer(m_Window, this);

		//Set glfwCallbacks
		SetGLFWCallbacks();
		m_LayerStack.PushOverlay(new WindowLayer(m_Window));
		m_LayerStack.PushOverlay(new UILayer());

		while (m_Running) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//find deltatime

			//update input
			//update renderer
			m_Engine.RenderUI();
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
		SET_GLFW_CALLBACK(m_Window, glfwSetWindowSizeCallback, WindowResize);
		SET_GLFW_CALLBACK(m_Window, glfwSetWindowCloseCallback, [](auto...) { return WindowClose(true); });
		SET_GLFW_CALLBACK(m_Window, glfwSetWindowFocusCallback, WindowFocus);	
	}		





}
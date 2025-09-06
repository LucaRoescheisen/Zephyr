#include "zppch.h"
#include "Application.h"
#include "Events/Event.h"
#include "Log.h"

#include "zppch.h"
#define SET_GLFW_CALLBACK(window, callbackFn, EventExpr)\
		callbackFn(window, [](GLFWwindow* win, auto... args){\
			Application* app = static_cast<Application*>(glfwGetWindowUserPointer(win)); \
			app->OnEvent(EventExpr(args...)); \
		});



namespace Zephyr {



	void Application::Run() {	
		m_Engine.InitWindow(m_Window, 1920, 1080, "Zephyr");
		glfwSetWindowUserPointer(m_Window, this);
		m_EditorUI.InitEditorUI(m_Window);
		//Set glfwCallbacks
		SetGLFWCallbacks();

		WindowLayer* windowLayer = new WindowLayer(m_Window, m_Engine, m_EditorUI);
		UILayer* uiLayer = new UILayer();

		m_LayerStack.PushOverlay(windowLayer);
		m_LayerStack.PushOverlay(uiLayer);

		while (m_Running) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			//find deltatime

			//update input
			//update renderer

			glfwPollEvents();
			m_EditorUI.RenderEditorUI();

			//render
			
			glfwSwapBuffers(m_Window);

			
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
		SET_GLFW_CALLBACK(m_Window, glfwSetWindowIconifyCallback, [](int iconified) {return WindowMinimise(iconified == GLFW_TRUE);});
		
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* win, int button, int action, int mod) {
			Application* app = static_cast<Application*>(glfwGetWindowUserPointer(win));
			if (ImGui_ImplGlfw_MouseButtonCallback)
				ImGui_ImplGlfw_MouseButtonCallback(win, button, action, mod);

			if (action == GLFW_PRESS) {
				app->OnEvent(MouseButtonPressed(button));
			}
			else if (action == GLFW_RELEASE) {
				app->OnEvent(MouseButtonReleased(button));
			}
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* win, int key, int scanCode, int action, int mod) {
			Application* app = static_cast<Application*>(glfwGetWindowUserPointer(win));
			if (action == GLFW_PRESS) {
				app->OnEvent(KeyPressed(key));
			}
			else if (action == GLFW_RELEASE) {
				app->OnEvent(KeyReleased(key));
			}
			
			});
	}		
}
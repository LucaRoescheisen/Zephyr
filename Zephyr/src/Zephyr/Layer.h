#pragma once
#include "Events/Event.h"
#include "zppch.h"

#define	ZP_BIND_EVENT_FN(type) std::bind(&type, type, std::placeholders::_1);


namespace Zephyr {

	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		void OnDetach() {};
		 void OnUpdate(float deltaTime);
		virtual void OnEvent(Event& ev) {};

		
	};

	class LayerStack {

	public:
		//Destructor to clear layers from memory
		~LayerStack() {
			for (Layer* layer : m_Layers) {
				delete layer;
			}
		
		}

		void PushLayer(Layer* layer) {
			m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);										//begin finds first entry and then we add
			m_LayerInsertIndex++;																				//Emplace pushes the rest back e.g. [l,O] -> [l, ,O] -> [l,l,O]
			layer->OnAttach();																					//Echo
		}

		void PopLayer(Layer* layer) {
			auto removedLayer = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);		//We look between two boundaries to find the layer
				if (removedLayer != m_Layers.begin() + m_LayerInsertIndex) {
					m_Layers.erase(removedLayer);
					m_LayerInsertIndex--;
				}
		}

		void PushOverlay(Layer* overlay) {
			m_Layers.emplace_back(overlay);
			overlay->OnAttach();
		}

		void PopOverlay(Layer* overlay) {
			auto removedOverlay = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
			if (removedOverlay != m_Layers.end()) {
				m_Layers.erase(removedOverlay);
			}
		}

		auto rbegin() { return m_Layers.rbegin(); }
		auto rend() { return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;



	};

	class WindowLayer: public Layer {
	public:
		WindowLayer(GLFWwindow* window) : m_Window(window) {}

		void OnEvent(Event& ev) {
			EventDispatcher dispatcher(ev);
			dispatcher.Dispatch<WindowResize>([this](WindowResize& ev) {
				OnWindowResize(ev);
				ZP_CORE_TRACE(ev.ToString());
				return true;										
				});
			dispatcher.Dispatch<WindowFocus>([this](WindowFocus& ev) {
				ZP_CORE_TRACE(ev.ToString());
				return true;
				});
		}

		void OnAttach() { ZP_CORE_TRACE("WindowLayer attached"); }
		void OnDetach() { ZP_CORE_TRACE("WindowLayer detached"); };
	private:
		GLFWwindow* m_Window;
		bool m_PreviouslyFocused = true;

		void OnWindowResize(WindowResize& ev) {
			glfwSetWindowSize(m_Window, ev.GetWidth(), ev.GetHeight());
		}

		
	};

	class UILayer : public Layer {

	public:
		void OnAttach() { ZP_CORE_TRACE("UILayer attached"); };
		void OnDetach() { ZP_CORE_TRACE("UILayer detached"); };


	};


}
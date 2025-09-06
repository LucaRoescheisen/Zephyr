#pragma once
#include "Events/Event.h"
#include "zppch.h"

#define	ZP_BIND_EVENT_FN(type) std::bind(&type, type, std::placeholders::_1);


namespace Zephyr {

	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		 void OnUpdate(float deltaTime);
		virtual void OnEvent(Event& ev) {};

	protected:
		 bool m_Active = true;
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
					delete *removedLayer;
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
				overlay->OnDetach();
				delete *removedOverlay;
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
		WindowLayer(GLFWwindow* window, Engine& engine, EditorUI& editorUI) : m_Window(window), m_Engine(engine), m_EditorUI(editorUI){}

		virtual void OnEvent(Event& ev) {
			if (!m_Active) { return; }
			EventDispatcher dispatcher(ev);
			dispatcher.Dispatch<WindowResize>([this](WindowResize& ev) {
				m_EditorUI.OnWindowResize(ev.GetWidth(), ev.GetHeight()); //Propogates new sizes to the Editor UI!!!!
				ZP_CORE_TRACE(ev.ToString());
				return true;
				});
			dispatcher.Dispatch<WindowFocus>([this](WindowFocus& ev) {
				
				ZP_CORE_TRACE(ev.ToString());
				return true;
				});
			dispatcher.Dispatch<WindowMinimise>([this](WindowMinimise& ev) {
				m_Engine.OnMinimiseEvent(ev.GetMinimisedState());			//Propogates whether application is minimised so we can halt rendering
				ZP_CORE_TRACE(ev.ToString());
				return true;
				});

			dispatcher.Dispatch<MouseButtonPressed>([this](MouseButtonPressed& ev) {		//Propogates whether application is minimised so we can halt rendering
				ImGuiIO& io = ImGui::GetIO();
				if (io.WantCaptureMouse) {													//Checks if ImGui should absorb the click
					ZP_CORE_TRACE("ImGui absorbed mouse");
					return false;
				}
				
				ZP_CORE_TRACE(ev.ToString());
				return true;
				});

			dispatcher.Dispatch<MouseButtonReleased>([this](MouseButtonReleased& ev) {		//Propogates whether application is minimised so we can halt rendering
				ZP_CORE_TRACE(ev.ToString());
				return true;
				});

			dispatcher.Dispatch<KeyPressed>([this](KeyPressed& ev) {
				ZP_CORE_TRACE(ev.ToString());
				return true;
				});

			dispatcher.Dispatch<KeyReleased>([this](KeyReleased& ev) {
				ZP_CORE_TRACE(ev.ToString());
				return true;
				});
		}

		virtual void OnAttach() { ZP_CORE_TRACE("WindowLayer attached"); }
		virtual void OnDetach() { ZP_CORE_TRACE("WindowLayer detached"); }
	private:
		GLFWwindow* m_Window;
		EditorUI& m_EditorUI;
		Engine& m_Engine;					//Reference as WindowLayer should not own the engine
		bool m_PreviouslyFocused = true;		
	};

	class UILayer : public Layer {

	public:
		virtual void OnAttach() { ZP_CORE_TRACE("UILayer attached"); };
		virtual void OnDetach() { ZP_CORE_TRACE("UILayer detached"); };


	};


}
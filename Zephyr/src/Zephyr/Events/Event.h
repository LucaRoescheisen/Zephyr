#pragma once
#include <sstream>
#include "Zephyr/Core.h"
namespace Zephyr {

	enum EventType {
		EventTypeNone = 0,
		WindowCloseEvent,
		WindowResizeEvent,
		WindowFocusEvent,
		WindowMinimiseEvent,
		WindowMovedEvent,
		AppTickEvent,
		AppUpdateEvent,
		AppRenderEvent,
		KeyPressedEvent,
		KeyReleasedEvent,
		MouseButtonPressedEvent,
		MouseButtonReleasedEvent,
		MouseMovedEvent,
		MouseScrolledEvent
	};


	enum EventCategory {
		EventCategoryNone        = 0,
		EventCategoryWindow      = 1 << 1,
		EventCategoryInput       = 1 << 2,
		EventCategoryMouse       = 1 << 3,
		EventCategoryKeyboard    = 1 << 4,
		EventCategoryMouseButton = 1 << 5,
	};


	#define EVENT_CLASS_TYPE(type) \
		static EventType GetStaticType() {return EventType::type; } \
		virtual EventType GetEventType() const override {return GetStaticType();}\
		virtual const char* GetName() const override {return #type;}

	


	class ZEPHYR_API Event {
	public:
		virtual EventType GetEventType() const = 0;
		virtual unsigned int GetCategoryFlag() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); };

		bool IsHandled() const { return m_Handled; }
	protected:
		bool m_Handled = false;
		friend class EventDispatcher;
	};


	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;							// Creates an empty template of what the function should accept				
																			//			
	public:																	//			
		EventDispatcher(Event& event) : m_Event(event) {}					//					

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);					//&m_Event is a reference to the Event Class
				return true;												//Where it is casted to T(where T can be a WindowResizeEvent)
			}																//You pass it into fun which is a lambda
			return false;
		}
		
	private:
		Event& m_Event;

	};


	class WindowClose : public Event {
	public:
		WindowClose(bool shouldClose) : m_HandleClose(shouldClose){}

		EVENT_CLASS_TYPE(WindowCloseEvent);

		bool IsCloseRequested() { return m_HandleClose; }

		virtual unsigned int GetCategoryFlag() const override {
			return EventCategoryWindow;
		}


		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowCloseEvent " << m_HandleClose;
			return ss.str();
		}

	private:
		bool m_HandleClose;
	};


	class WindowMinimise : public Event {
	public:
		WindowMinimise(int iconified)
			: m_IsMinimised(iconified) {
		}

		EVENT_CLASS_TYPE(WindowMinimiseEvent);
		unsigned int GetCategoryFlag() const override { return EventCategoryWindow; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowMinimiseEvent " << m_IsMinimised;
			return ss.str();
		}

		int GetMinimisedState() {
			return m_IsMinimised;
		}

	private:
		int m_IsMinimised;		//Is 1 if application is minimised
	};



	class WindowResize : public Event {
	public:
		WindowResize(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

		EVENT_CLASS_TYPE(WindowResizeEvent);

		unsigned int GetWidth() { return m_Width; }
		unsigned int GetHeight() { return m_Height; }

		virtual unsigned int GetCategoryFlag() const override {
		return EventCategoryWindow;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent " << m_Width << ", " << m_Height;
			return ss.str();
		}
		
	private:
		unsigned int m_Width, m_Height;
	};


	class WindowFocus : public Event {
	public:
		WindowFocus(int isFocused) : m_Focused(isFocused) {}

		EVENT_CLASS_TYPE(WindowFocusEvent);

		bool IsFocusNotLost() { return m_Focused; }


		virtual unsigned int GetCategoryFlag() const override {
			return EventCategoryWindow;
		}


		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowFocusEvent " << m_Focused;
			return ss.str();
		}
	private:
		int m_Focused;
		
	};

	//-----------------------------------------------Mouse Events--------------------------------------------------//
	class MouseButton : public Event {
	public:
		int GetMouseButton() const { return m_MouseButton; }

		virtual unsigned int GetCategoryFlag() const override {
			return EventCategoryMouse | EventCategoryMouseButton;
		}

	protected:
		MouseButton(int button) : m_MouseButton(button) {}
		int m_MouseButton;
	};

	class MouseButtonPressed : public MouseButton {
	public:
		MouseButtonPressed(int mouseButton) : MouseButton(mouseButton) {}

		EVENT_CLASS_TYPE(MouseButtonPressedEvent);

		virtual unsigned int GetCategoryFlag() const override {
			return EventCategoryMouseButton;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MousePressedEvent " << m_MouseButton;
			return ss.str();
		}

	};

	class MouseButtonReleased: public MouseButton {
	public:
		MouseButtonReleased(int mouseButton) : MouseButton(mouseButton) {}

		EVENT_CLASS_TYPE(MouseButtonReleasedEvent);

		virtual unsigned int GetCategoryFlag() const override {
			return EventCategoryMouseButton;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseReleasedEvent " << m_MouseButton;
			return ss.str();
		}

	};

	//-------------------------------------Keyboard Events-------------------------------------//
	class KeyButton : public Event {
	public:
		int GetKeyButton() const { return m_Key; };

		virtual unsigned int GetCategoryFlag() const override {
			return EventCategoryKeyboard;
		}

	protected:
		KeyButton(int key) : m_Key(key) {}
		int m_Key;
	};


	class KeyPressed : public KeyButton {
	public:
		KeyPressed(int keyButton) : KeyButton(keyButton) {}

		EVENT_CLASS_TYPE(KeyPressedEvent);

		virtual unsigned int GetCategoryFlag() const override {
			return EventCategoryKeyboard;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent " << m_Key;
			return ss.str();
		}
	};

	class KeyReleased : public KeyButton {
	public:
		KeyReleased(int keyButton) : KeyButton(keyButton) {}

		EVENT_CLASS_TYPE(KeyReleasedEvent);

		virtual unsigned int GetCategoryFlag() const override {
			return EventCategoryKeyboard;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent " << m_Key;
			return ss.str();
		}
	};

}


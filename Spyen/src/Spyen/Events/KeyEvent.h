#pragma once
#include "spypch.h"
#include "Event.h"

namespace Spyen{
	class KeyEvent : public Event {
	public:
		inline SDL_Scancode GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) {}
		SDL_Scancode m_KeyCode;		
	};
}
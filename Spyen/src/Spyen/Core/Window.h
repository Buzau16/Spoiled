#pragma once

#include "spypch.h"
#include "Events/Event.h"

// TODO : EVENT SYSTEM

namespace Spyen {

	struct WindowData
	{
		std::string Title;
		uint32_t Width, Height;
		bool VSync;
		using EventCallbackFn = std::function<void(Event&)>;
		EventCallbackFn EventCallback;
	};

	class Window
	{
	public:
		Window();
		~Window() = default;
		
		virtual void Init(const char* title, uint32_t width, uint32_t height) = 0;
		virtual void Destroy() = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void SwapBuffers() = 0;
		virtual bool IsOpen() = 0;
		virtual void PollEvents() = 0;

		inline void SetEventCallback(const WindowData::EventCallbackFn& callback) { m_Data.EventCallback = callback; };
		inline uint32_t GetWidth() const { return m_Data.Width; }
		inline uint32_t GetHeight() const { return m_Data.Height; }

	private:
		SDL_Window* m_Window;
		WindowData m_Data;
	};

}

#pragma once

#include "spypch.h"
#include <glfw/glfw3.h>
#include "Events/Event.h"

// TODO : EVENT SYSTEM

namespace Spyen {

	struct WindowData
	{
		using EventCallbackFn = std::function<void(Event&)>;
		EventCallbackFn EventCallback;
		std::string Title;
		uint32_t Width, Height;
		bool VSync;
	};

	class Window
	{
	public:
		Window();
		~Window() = default;
		
		void Init(const char* title, uint32_t width, uint32_t height);
		void Destroy();
		void SetVSync(bool enabled);
		void SwapBuffers();
		bool IsOpen();
		void PollEvents();
		void Clear(float r, float g, float b);

		inline void SetEventCallback(const WindowData::EventCallbackFn& callback) { m_Data.EventCallback = callback; };
		inline uint32_t GetWidth() const { return m_Data.Width; }
		inline uint32_t GetHeight() const { return m_Data.Height; }

	private:
		GLFWwindow* m_Window;
		WindowData m_Data;
	};

}

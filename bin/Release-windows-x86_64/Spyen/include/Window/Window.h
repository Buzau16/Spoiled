#pragma once
#include "Core/Core.h"
#include <string>
// TODO : EVENT SYSTEM

struct GLFWwindow;

namespace Spyen {

	struct WindowData
	{
		std::string Title;
		uint32_t Width, Height;
		bool VSync;
	};

	class SPYEN_API Window
	{
	public:
		Window();
		~Window() = default;
		
		void Init(const std::string& title,  uint32_t width, uint32_t height);
		void Destroy();
		void SetVSync(bool enabled);
		void SwapBuffers();
		bool IsOpen();
		void PollEvents();
		void Clear(float r, float g, float b);

		//inline void SetEventCallback(const WindowData::EventCallbackFn& callback) { m_Data.EventCallback = callback; };
		inline uint32_t GetWidth() const { return m_Data.Width; }
		inline uint32_t GetHeight() const { return m_Data.Height; }


	private:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
		static void WindowResizeCallback(GLFWwindow* window, int width, int height);
		void SetCallbacks();

		GLFWwindow* m_Window;
		WindowData m_Data;
	};

}

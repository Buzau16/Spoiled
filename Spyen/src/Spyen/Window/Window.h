#pragma once

#include "spypch.h"

// TODO : EVENT SYSTEM

namespace Spyen {
	class Window
	{

	public:
		Window();
		~Window() = default;
		
#ifndef SP_GL
		void Init(const char* title, uint32_t width, uint32_t height);
#else
		// VULKAN INITIALIZATION
#endif // !SPY_GL

		bool IsOpen();
		void Destroy();

	private:
		SDL_Window* m_Window;
		SDL_GLContext m_Context;

		uint32_t m_Width;
		uint32_t m_Height;
		std::string m_Title;
	};

}

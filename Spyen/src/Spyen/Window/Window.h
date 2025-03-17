#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <GL/glew.h>


namespace Spyen {
	class Window
	{

	public:
		Window() = default;
		~Window() = default;

		void Init(std::string& title, uint32_t width, uint32_t height);
		void Destroy();

	private:
		SDL_Window* m_Window;
		SDL_GLContext m_Context;

		uint32_t m_Width;
		uint32_t m_Height;
		std::string m_Title;
	};

}

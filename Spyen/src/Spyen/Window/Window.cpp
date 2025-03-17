#include "spypch.h"

#include "Window.h"

namespace Spyen {

	Window::Window()
		: m_Window(nullptr),
		  m_Context(nullptr),
		  m_Width(0),
		  m_Height(0)
	{}

	void Window::Init(const char* title, uint32_t width, uint32_t height)
	{
		m_Width = width;
		m_Height = height;
		m_Title = title;


		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cerr << "Error initalizing SDL: " << SDL_GetError();
			return;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_GL_SetSwapInterval(0);

		m_Window = SDL_CreateWindow(m_Title.c_str(), 200, 200, m_Width, m_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		if (!m_Window) {
			std::cerr << "Error initializing window: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return;
		}

		m_Context = SDL_GL_CreateContext(m_Window);
		if (!m_Context) {
			std::cerr << "Error creating OpenGL context: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(m_Window);
			SDL_Quit();
			return;
		}

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to initalize GLEW!\n";
			SDL_GL_DeleteContext(m_Context);
			SDL_DestroyWindow(m_Window);
			SDL_Quit();
		}

		glViewport(0, 0, m_Width, m_Height);
		glEnable(GL_DEPTH_TEST);
	}

	bool Window::IsOpen()
	{
		return m_Window != nullptr;
	}

	void Window::Destroy()
	{
		SDL_GL_DeleteContext(m_Context);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}
};
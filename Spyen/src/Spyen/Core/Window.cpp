#include "spypch.h"

#include "Window.h"

namespace Spyen {
	Window::Window():
		m_Window(nullptr),
		m_Data({ nullptr, "", 0, 0, false })
	{
	}

	void Window::Init(const char* title, uint32_t width, uint32_t height)
	{
		m_Data.Title = title;
		m_Data.Width = width;
		m_Data.Height = height;

		if (!glfwInit()) {
			std::cerr << "Failed to initialize GLFW" << std::endl;
			return;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!m_Window) {
			std::cerr << "Failed to create window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_Window);

		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			std::cerr << "Failed to initialize GLEW" << std::endl;
			glfwDestroyWindow(m_Window);
			glfwTerminate();
			return;
		}

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, width, height);


		glfwSetWindowUserPointer(m_Window, &m_Data);
	}

	void Window::Destroy()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	void Window::SetVSync(bool enabled)
	{
		if (enabled) {
			m_Data.VSync = true;
			glfwSwapInterval(m_Data.VSync);
		}
		else {
			m_Data.VSync = false;
			glfwSwapInterval(m_Data.VSync);
		}
	}
	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	bool Window::IsOpen()
	{
		return !glfwWindowShouldClose(m_Window);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}
	void Window::Clear(float r, float g, float b)
	{
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
};
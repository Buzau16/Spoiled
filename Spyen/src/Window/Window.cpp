#include "spypch.h"
#include "Window/Window.h"
#include "Input/Input.h"

namespace Spyen {
	Window::Window() :
		m_Window(nullptr),
		m_Data({"", 0, 0})
	{
	}

	void Window::Init(const std::string& title, uint32_t width, uint32_t height)
	{
		SPY_CORE_INFO("Creating Window: {0} with dimensions: ({1} x {2})", title, width, height);
		m_Data.Title = title;
		m_Data.Width = width;
		m_Data.Height = height;

		

		if (!glfwInit())
			SPY_CORE_CRITICAL("Failed to initialize Glew");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		SPY_CORE_ASSERT(m_Window, "Failed to create window");

		glfwMakeContextCurrent(m_Window);

		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK ) {
			std::cerr << "Failed to initialize GLEW" << std::endl;
			glfwDestroyWindow(m_Window);
			glfwTerminate();
			return;
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE); 
		glCullFace(GL_BACK);     
		glFrontFace(GL_CCW);
		glViewport(0, 0, width, height);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);


		glfwSetWindowUserPointer(m_Window, &m_Data);
		
		SetCallbacks();
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

	void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			Input::SetKeyState(key, true);
		}
		if (action == GLFW_RELEASE) {
			Input::SetKeyState(key, false);
		}
	}

	void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			Input::SetMouseButtonState(button, true);
		}
		if (action == GLFW_RELEASE) {
			Input::SetKeyState(button, false);
		}
	}

	void Window::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Input::SetMousePosition(static_cast<float>(xpos), static_cast<float>(ypos));
	}

	void Window::WindowResizeCallback(GLFWwindow* window, int width, int height)
	{
		Input::SetWindowSize(width, height);
		glViewport(0, 0, width, height);
	}

	void Window::SetCallbacks()
	{
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, MouseMoveCallback);
		glfwSetFramebufferSizeCallback(m_Window, WindowResizeCallback);
	}
};
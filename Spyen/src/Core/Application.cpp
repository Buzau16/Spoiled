
#include "spypch.h"
#include "Application.h"


namespace Spyen {
	void SetBackgroundColor(float r, float g, float b, float a)
	{
		s_BackgroundColor = { r, g, b };
	}
	void InitWindow(const char* title, uint32_t width, uint32_t height)
	{
		s_Window.Init(title, height, height);
	}

	void Init()
	{
		Renderer::Init();
	}

	void AddQuad(const Vector2& vect)
	{
		Renderer::AddQuad(vect);
	}

	void Run()
	{
		
		while (s_Window.IsOpen()) {

			s_Window.PollEvents();

			Time::UpdateTime();

			s_Window.Clear(s_BackgroundColor.r, s_BackgroundColor.g, s_BackgroundColor.b);

			// Render
			Renderer::BeginBatch();
			for (int i = 0; i < Renderer::s_QuadVertices.size(); i++)
				Renderer::SubmitQuad(Renderer::s_QuadVertices[i]);
			Renderer::EndBatch();

			s_Window.SwapBuffers();
		}
		s_Window.Destroy();
		Renderer::Shutdown();
	}
}
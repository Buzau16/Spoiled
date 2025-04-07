
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

	void AddEntity(std::unique_ptr<Entity> entity)
	{
		s_Entities.push_back(std::move(entity));
	}

	void Run()
	{
		float LastFrameTime = 0.0f;

		while (s_Window.IsOpen()) {

			s_Window.PollEvents();

			float time = glfwGetTime();
			Timestep ts = time - LastFrameTime;
			LastFrameTime = time;

			s_Window.Clear(s_BackgroundColor.r, s_BackgroundColor.g, s_BackgroundColor.b);

			Renderer::BeginBatch();
			// Update + Render
			for (auto& entity : s_Entities) {
				entity->OnUpdate(ts);
				entity->OnRender();
			}

			Renderer::EndBatch();

			s_Window.SwapBuffers();
		}
		s_Window.Destroy();
		Renderer::Shutdown();
	}
}
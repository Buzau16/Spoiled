
#include "spypch.h"
#include "Application.h"


namespace Spyen {

	

	void SetBackgroundColor(float r, float g, float b, float a)
	{
		s_BackgroundColor = { r, g, b };
	}

	void AddEntity(std::unique_ptr<Entity> entity)
	{
		//SPY_CORE_INFO("Adding Entity: {0}", entity->GetName());
		s_Entities.push_back(std::move(entity));
	}

	void Init(const std::string& title, uint32_t width, uint32_t height)
	{
		Log::Init();
		SPY_CORE_INFO("Initializing Spyen");
		SPY_CORE_INFO("Initializing Logger");
		s_Window.Init(title, height, height);
		Renderer::Init();
		AssetManager::Init();
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

#include "spypch.h"
#include "Application.h"

#include <cstdlib>



namespace Spyen {

	Engine::Data Engine::s_EngineData;

	void Engine::SetBackgroundColor(float r, float g, float b, float a)
	{
		s_EngineData.BackgroundColor = { r, g, b };
	}

	void Engine::Init(const std::string& title, uint32_t width, uint32_t height)
	{
		Log::Init();
		SPY_CORE_INFO("Initializing Spyen");
		SPY_CORE_INFO("Initializing Logger");
		s_EngineData.Window.Init(title, height, height);
		Renderer::Init();
		AssetManager::Init();
	}

	void Engine::Run()
	{
		float LastFrameTime = 0.0f;

		while (s_EngineData.Window.IsOpen()) {

			glfwSwapInterval(0);

			Input::Update();
			s_EngineData.Window.PollEvents();

			float time = glfwGetTime();
			Timestep ts = time - LastFrameTime;
			LastFrameTime = time;

			s_EngineData.Window.Clear(s_EngineData.BackgroundColor.r, s_EngineData.BackgroundColor.g, s_EngineData.BackgroundColor.b);

			Renderer::BeginFrame();
			// Update + Render on dynamic objects
			//for (auto& obj : s_EngineData.DynamicObjects) {
			//	obj->OnUpdate(ts);
			//	obj->OnRender();
			//}

			//// Only render static objects
			//for (auto& obj : s_EngineData.StaticObjects) {
			//	obj->OnRender();
			
			s_EngineData.ActiveScene.OnUpdate(ts);
			s_EngineData.ActiveScene.OnRender();

			Renderer::EndFrame();

			//std::cout << "FPS: " << 1.f / ts << std::endl;

			s_EngineData.Window.SwapBuffers();
		}
		s_EngineData.Window.Destroy();
		Renderer::Shutdown();
	}
}
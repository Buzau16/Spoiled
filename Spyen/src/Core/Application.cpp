
#include "spypch.h"
#include "Core/Application.h"
#ifdef SP_DEBUG
#include <vld.h>
#endif

#include <cstdlib>

namespace Spyen {

	struct EngineData {
		Window Window;
		Color BackgroundColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		std::shared_ptr<Scene> ActiveScene;
		std::unordered_map<std::string, std::shared_ptr<Scene>> Scenes;
	};

	static EngineData s_EngineData;

	void Engine::SetBackgroundColor(float r, float g, float b, float a)
	{
		s_EngineData.BackgroundColor = { r, g, b };
	}

	void Engine::AddScene(std::shared_ptr<Scene> scene)
	{
		s_EngineData.Scenes[scene->GetName()] = scene;
	}
	void Engine::SetActiveScene(const char* name)
	{
		s_EngineData.ActiveScene = s_EngineData.Scenes[name];
	}

	std::shared_ptr<Scene> Engine::GetActiveScene()
	{
		return s_EngineData.ActiveScene;
	}

	void Engine::Init(const std::string& title, uint32_t width, uint32_t height)
	{
		Log::Init();
		SPY_CORE_INFO("Initializing Spyen");
		SPY_CORE_INFO("Initializing Logger");
		s_EngineData.Window.Init(title, height, height);
		AssetManager::LookForAssetsDirectory();
		Renderer::Init();
		SoundManager::Init();
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
			
			s_EngineData.ActiveScene->OnUpdate(ts);
			s_EngineData.ActiveScene->OnRender();

			Renderer::EndFrame();

			s_EngineData.Window.SwapBuffers();
		}
		s_EngineData.Window.Destroy();
		SoundManager::Shutdown();
		Renderer::Shutdown();
	}
}
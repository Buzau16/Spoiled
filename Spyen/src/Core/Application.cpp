
#include "spypch.h"
#include "Core/Application.h"
#ifdef SP_DEBUG
#include <vld.h>
#endif

#include <cstdlib>



// TODO: Modify the build system so that the .dlls are added to the ./bin folder 
// and the shaders are addded to it as well + any other external dependencies

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
		Renderer::Shutdown();
	}
}
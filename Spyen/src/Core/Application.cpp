
#include "spypch.h"
#include "Application.h"

#include <cstdlib>

Color g_BackgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};
Spyen::Window g_Window;
std::vector<std::unique_ptr<Spyen::StaticGameObject>> g_StaticObjects;
std::vector<std::unique_ptr<Spyen::DynamicGameObject>> g_DynamicObjects;

namespace Spyen {

	

	void SetBackgroundColor(float r, float g, float b, float a)
	{
		g_BackgroundColor = { r, g, b };
	}


	void Init(const std::string& title, uint32_t width, uint32_t height)
	{
		Log::Init();
		SPY_CORE_INFO("Initializing Spyen");
		SPY_CORE_INFO("Initializing Logger");
		g_Window.Init(title, height, height);
		Renderer::Init();
		AssetManager::Init();
	}

	void AddStaticObject(std::unique_ptr<StaticGameObject> obj)
	{
		obj->OnCreate();
		g_StaticObjects.push_back(std::move(obj));
	}

	void AddDynamicObject(std::unique_ptr<DynamicGameObject> obj)
	{
		obj->OnCreate();
		g_DynamicObjects.push_back(std::move(obj));
	}

	void Run()
	{
		float LastFrameTime = 0.0f;

		while (g_Window.IsOpen()) {

			glfwSwapInterval(0);

			Input::Update();
			g_Window.PollEvents();

			float time = glfwGetTime();
			Timestep ts = time - LastFrameTime;
			LastFrameTime = time;

			g_Window.Clear(g_BackgroundColor.r, g_BackgroundColor.g, g_BackgroundColor.b);

			Renderer::BeginFrame();
			// Update + Render on dynamic objects
			for (auto& obj : g_DynamicObjects) {
				obj->OnUpdate(ts);
				obj->OnRender();
			}

			// Only render static objects
			for (auto& obj : g_StaticObjects) {
				obj->OnRender();
			}

			Renderer::EndFrame();

			//std::cout << "FPS: " << 1.f / ts << std::endl;

			g_Window.SwapBuffers();
		}
		g_Window.Destroy();
		Renderer::Shutdown();
	}
}
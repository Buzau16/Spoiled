#pragma once

#include "Window/Window.h"
#include "Input/Input.h"
#include "Core/Base.h"
#include "Time/Timestep.h"
#include "Renderer/Renderer.h"
#include "Entity/Entity.h"
#include "Scene/Scene.h"



namespace Spyen {
	class Engine {
	public:
		static void Init(const std::string& title, uint32_t width, uint32_t height);
		static void SetBackgroundColor(float r, float g, float b, float a);
		//void InitWindow(const char* title, uint32_t width, uint32_t height);

		/*static void AddStaticObject(std::unique_ptr<StaticGameObject> obj);
		static void AddDynamicObject(std::unique_ptr<DynamicGameObject> obj);*/

		static void AddScene(Scene scene) { s_EngineData.Scenes.push_back(scene); };
		static void SetActiveScene(Scene scene) { s_EngineData.ActiveScene = scene; };


		static void Run();

	private:
		struct Data {
			Window Window;
			Color BackgroundColor = { 0.0f, 0.0f, 0.0f, 1.0f };
			/*std::vector<std::unique_ptr<Spyen::StaticGameObject>> StaticObjects;
			std::vector<std::unique_ptr<Spyen::DynamicGameObject>> DynamicObjects;*/
			Scene ActiveScene;
			std::vector<Scene> Scenes;
		};

		static Data s_EngineData;
	};
}


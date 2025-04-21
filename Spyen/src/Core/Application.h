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

		static void AddScene(std::shared_ptr<Scene> scene) { s_EngineData.Scenes[scene->GetName()] = scene; };
		static void SetActiveScene(const char* name) { s_EngineData.ActiveScene = s_EngineData.Scenes[name]; };
		static std::shared_ptr<Scene> GetActiveScene() { return s_EngineData.ActiveScene; };

		static void Run();

	private:
		struct Data {
			Window Window;
			Color BackgroundColor = { 0.0f, 0.0f, 0.0f, 1.0f };
			std::shared_ptr<Scene> ActiveScene;
			std::unordered_map<std::string, std::shared_ptr<Scene>> Scenes;
		};

		static Data s_EngineData;
	};
}


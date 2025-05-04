#pragma once

#include "Window/Window.h"
#include "Input/Input.h"
#include "Core/Structs.h"
#include "Time/Timestep.h"
#include "Renderer/Renderer.h"
#include "Scene/Scene.h"
#include "Core/Core.h"
#include "Audio/SoundManager.h"

// TODO: Make the "Sound Engine" use the miniaudio low-level api! ehhh
// TODO: Camera!


namespace Spyen {
	class SPYEN_API Engine {
	public:
		static void Init(const std::string& title, uint32_t width, uint32_t height);
		static void SetBackgroundColor(float r, float g, float b, float a);

		static void AddScene(std::shared_ptr<Scene> scene); 
		static void SetActiveScene(const char* name);
		static std::shared_ptr<Scene> GetActiveScene();

		static void Run();
	};
}


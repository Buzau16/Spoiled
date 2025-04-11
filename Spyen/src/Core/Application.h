#pragma once

#include "Window/Window.h"
#include "Input/Input.h"
#include "Core/Base.h"
#include "Time/Timestep.h"
#include "Renderer/Renderer.h"
#include "Entity/Entity.h"



namespace Spyen {
	void Init(const std::string& title, uint32_t width, uint32_t height);
	void SetBackgroundColor(float r, float g, float b, float a);
	//void InitWindow(const char* title, uint32_t width, uint32_t height);
	
	void AddStaticObject(std::unique_ptr<StaticGameObject> obj);
	void AddDynamicObject(std::unique_ptr<DynamicGameObject> obj);
	
	void Run();
}


#pragma once

#include "Window/Window.h"
#include "Input/Input.h"
#include "Core/Base.h"
#include "Time/Timestep.h"
#include "Renderer/Renderer.h"
#include "Entity/Entity.h"

static Color s_BackgroundColor = { 0.0f, 0.0f, 0.0f };
static Spyen::Window s_Window;
static std::vector<std::unique_ptr<Spyen::Entity>> s_Entities;

namespace Spyen {
	void Init(const std::string& title, uint32_t width, uint32_t height);
	void SetBackgroundColor(float r, float g, float b, float a);
	//void InitWindow(const char* title, uint32_t width, uint32_t height);
	

	void AddEntity(std::unique_ptr<Entity> entity);
	void Run();
}


#pragma once

#include "Window/Window.h"
#include "Input/Input.h"
#include "Core/Base.h"
#include "Time/Time.h"
#include "Renderer/Renderer.h"

static Color s_BackgroundColor = { 0.0f, 0.0f, 0.0f };
static Spyen::Window s_Window;
static std::vector<Spyen::Renderer> s_Quads;

namespace Spyen {
	void SetBackgroundColor(float r, float g, float b, float a);
	void InitWindow(const char* title, uint32_t width, uint32_t height);
	void Init();
	void AddQuad(const Vector2& position, const Color& color);
	void Run();
}


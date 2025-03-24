#pragma once

#include "Window/Window.h"
#include "Input/Input.h"
#include "Core/Base.h"
#include "Time/Time.h"

struct Color {
	float r, g, b;
};

static Color s_BackgroundColor = { 0.0f, 0.0f, 0.0f };
static Spyen::Window s_Window;
static Vector2 position = Vector2();

namespace Spyen {
	void SetBackgroundColor(float r, float g, float b, float a);
	void InitWindow(const char* title, uint32_t width, uint32_t height);
	void Run();
}


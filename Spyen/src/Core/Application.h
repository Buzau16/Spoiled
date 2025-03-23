#pragma once

#include "Window.h"
#include "Input/Input.h"

struct Color {
	float r, g, b;
};

static Color s_BackgroundColor = { 0.0f, 0.0f, 0.0f };
static Spyen::Window s_Window;

namespace Spyen {
	void SetBackgroundColor(float r, float g, float b, float a);
	void InitWindow(const char* title, uint32_t width, uint32_t height);
	void Run();
}


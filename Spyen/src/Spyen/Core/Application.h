#pragma once
#define SDL_MAIN_HANDLED

#include "spypch.h"
#include "Window.h"

namespace Spyen {
	static Window* s_Window;
	
	void InitWindow(const char* title, uint32_t width, uint32_t height);
	void Run();
}


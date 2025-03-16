#include "Application.h"


namespace Spyen {
	void InitWindow(std::string& title, uint32_t width, uint32_t height)
	{
		Window window;
		window.Init(title, width, height);
	}
}
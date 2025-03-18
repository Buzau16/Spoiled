#include "spypch.h"

#include "Application.h"


namespace Spyen {
	void InitWindow(const char* title, uint32_t width, uint32_t height)
	{
		s_Window = new Window();
		s_Window->Init(title, height, height);
	}

	void Run()
	{
		while (s_Window->IsOpen()) {
			s_Window->PollEvents();

			// Do stuff


			SDL_GL_SwapWindow(s_Window->GetWindow());
		}
		s_Window->Destroy();
		delete s_Window;
	}
}
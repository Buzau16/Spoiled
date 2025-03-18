#pragma once
#include "Core/Window.h"


namespace Spyen
{
	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow();
		~OpenGLWindow() = default;
		void Init(const char* title, uint32_t width, uint32_t height) override;
		void Destroy() override;
		void SetVSync(bool enabled) override;
		void SwapBuffers() override;
		bool IsOpen() override;
		void PollEvents() override;
	};
}



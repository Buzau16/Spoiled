#pragma once
#include <unordered_map>
#include "Core/Keycodes.h"
#include "Core/Mousecodes.h"

namespace Spyen {
	class Input
	{
	public:
		/////// KEYBOARD /////////
		static void SetKeyState(KeyCode code, bool pressed);
		static bool IsKeyPressed(KeyCode code);

		/////// MOUSE ///////////
		static void SetMouseButtonState(MouseCode code, bool pressed);
		static bool IsMouseButtonPressed(MouseCode code);

		static void SetMousePosition(float x, float y);
		static inline float GetMouseX();
		static inline float GetMouseY();


		/////// WINDOW //////////
		static void SetWindowSize(uint32_t width, uint32_t height);

		static inline uint32_t GetWindowWidth();
		static inline uint32_t GetWindowHeight();

	private:
		static std::unordered_map<KeyCode, bool> s_Keys;
		static std::unordered_map<MouseCode, bool> s_MouseButtons;
		static float s_MouseX;
		static float s_MouseY;
		static float s_WindowWidth;
		static float s_WindowHeight;
	};
}

#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#include <unordered_map>
#include "Core/Keycodes.h"
#include "Core/Mousecodes.h"

namespace Spyen {
	class SPYEN_API Input
	{
	public:
		inline static void Update();

		/////// KEYBOARD /////////
		inline static void SetKeyState(KeyCode code, bool pressed);
		inline static bool IsKeyDown(KeyCode code);
		inline static bool IsKeyPressed(KeyCode code);
		inline static bool IsKeyUp(KeyCode code);

		/////// MOUSE ///////////
		inline static void SetMouseButtonState(MouseCode code, bool pressed);
		inline static bool IsMouseButtonPressed(MouseCode code);

		inline static void SetMousePosition(float x, float y);
		inline static float GetMouseX();
		inline static float GetMouseY();


		/////// WINDOW //////////
		inline static void SetWindowSize(uint32_t width, uint32_t height);

		inline static uint32_t GetWindowWidth();
		inline static uint32_t GetWindowHeight();
	};
}

#pragma warning(pop)
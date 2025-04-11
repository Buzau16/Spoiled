#include "spypch.h"
#include "Input.h"


namespace Spyen {

	std::unordered_map<KeyCode, bool> Input::s_Keys;
	std::unordered_map<MouseCode, bool> Input::s_MouseButtons;
	std::unordered_map<KeyCode, bool> Input::s_PrevKeys;
	float Input::s_MouseX;
	float Input::s_MouseY;
	float Input::s_WindowWidth;
	float Input::s_WindowHeight;

	void Input::SetKeyState(KeyCode code, bool pressed)
	{
		s_Keys[code] = pressed;
	}

	bool Input::IsKeyDown(KeyCode code)
	{
		return s_Keys[code] && !s_PrevKeys[code];
	}

	bool Input::IsKeyPressed(KeyCode code)	
	{
		return s_Keys[code];
	}

	bool Input::IsKeyUp(KeyCode code)
	{
		return !s_Keys[code] && s_PrevKeys[code];
	}

	void Input::SetMouseButtonState(MouseCode code, bool pressed)
	{
		s_MouseButtons[code] = pressed;
	}

	bool Input::IsMouseButtonPressed(MouseCode code)
	{
		return s_MouseButtons[code];
	}

	void Input::SetMousePosition(float x, float y)
	{
		s_MouseX = x;
		s_MouseY = y;
	}

	inline float Input::GetMouseX()
	{
		return s_MouseX;
	}

	inline float Input::GetMouseY()
	{
		return s_MouseY;
	}

	void Input::SetWindowSize(uint32_t width, uint32_t height)
	{
		s_WindowWidth = width;
		s_WindowHeight = height;
	}

	inline uint32_t Input::GetWindowWidth()
	{
		return s_WindowWidth;
	}

	inline uint32_t Input::GetWindowHeight()
	{
		return s_WindowHeight;
	}


}

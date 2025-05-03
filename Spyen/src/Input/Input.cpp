#include "spypch.h"
#include "Input/Input.h"


namespace Spyen {

	struct InputData {
		std::unordered_map<KeyCode, bool> Keys;
		std::unordered_map<KeyCode, bool> PrevKeys;
		std::unordered_map<MouseCode, bool> MouseButtons;
		float MouseX;
		float MouseY;
		float WindowWidth;
		float WindowHeight;
	};

	static InputData s_Data;


	void Input::Update()
	{
		s_Data.PrevKeys = s_Data.Keys;
	}

	void Input::SetKeyState(KeyCode code, bool pressed)
	{
		s_Data.Keys[code] = pressed;
	}

	bool Input::IsKeyDown(KeyCode code)
	{
		return s_Data.Keys[code] && !s_Data.PrevKeys[code];
	}

	bool Input::IsKeyPressed(KeyCode code)	
	{
		return s_Data.Keys[code];
	}

	bool Input::IsKeyUp(KeyCode code)
	{
		return !s_Data.Keys[code] && s_Data.PrevKeys[code];
	}

	void Input::SetMouseButtonState(MouseCode code, bool pressed)
	{
		s_Data.MouseButtons[code] = pressed;
	}

	bool Input::IsMouseButtonPressed(MouseCode code)
	{
		return s_Data.MouseButtons[code];
	}

	void Input::SetMousePosition(float x, float y)
	{
		s_Data.MouseX = x;
		s_Data.MouseY = y;
	}

	inline float Input::GetMouseX()
	{
		return s_Data.MouseX;
	}

	inline float Input::GetMouseY()
	{
		return s_Data.MouseY;
	}

	void Input::SetWindowSize(uint32_t width, uint32_t height)
	{
		s_Data.WindowWidth = width;
		s_Data.WindowHeight = height;
	}

	inline uint32_t Input::GetWindowWidth()
	{
		return s_Data.WindowWidth;
	}

	inline uint32_t Input::GetWindowHeight()
	{
		return s_Data.WindowHeight;
	}


}

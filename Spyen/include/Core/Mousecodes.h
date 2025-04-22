#pragma once

#include <stdint.h>

namespace Spyen {

	using MouseCode = uint32_t;

	enum : MouseCode {
		// From glfw3.h
		SPK_MOUSE_BUTTON_0 = 0,
		SPK_MOUSE_BUTTON_1 = 1,
		SPK_MOUSE_BUTTON_2 = 2,
		SPK_MOUSE_BUTTON_3 = 3,
		SPK_MOUSE_BUTTON_4 = 4,
		SPK_MOUSE_BUTTON_5 = 5,
		SPK_MOUSE_BUTTON_6 = 6,
		SPK_MOUSE_BUTTON_7 = 7,
		SPK_MOUSE_BUTTON_Last = SPK_MOUSE_BUTTON_7,
		SPK_MOUSE_BUTTON_Left = SPK_MOUSE_BUTTON_0,
		SPK_MOUSE_BUTTON_Right = SPK_MOUSE_BUTTON_1,
		SPK_MOUSE_BUTTON_Middle = SPK_MOUSE_BUTTON_2
	};
}
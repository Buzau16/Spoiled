#pragma once
#include "Core/Core.h"

namespace Spyen {
	struct SPYEN_API Color {
		float r, g, b, a;

		Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {};
		Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {};

	};


	struct SPYEN_API Vector2 {

		float x, y;

		Vector2() : x(0.0f), y(0.0f) {}
		Vector2(float x, float y) : x(x), y(y) {}

		Vector2& operator+=(const Vector2& other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}
	};

}


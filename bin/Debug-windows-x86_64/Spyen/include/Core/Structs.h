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

	struct SPYEN_API Vector3 {
		float x, y, z;

		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		Vector3& operator+=(const Vector3& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}
	};

	struct SPYEN_API Vector4 {
		float x, y, z, w;

		Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

		Vector4& operator+=(const Vector4& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;
			return *this;
		}
	};

}


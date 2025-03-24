#pragma once

#define BIT(x) (1 << x)

struct Vector2 {
	float x, y;

	Vector2(float x, float y) : x(x), y(y){};
	Vector2() : x(0), y(0) {};
};

#pragma once

#define BIT(x) (1 << x)

struct Vector2 {
	float x, y;
	float rotation;
	float scale;

	Vector2(float x, float y, float rot, float s) : x(x), y(y), rotation(rot), scale(s) {};
	Vector2() : x(0), y(0), rotation(0), scale(1) {};
};

struct Color {
	float r, g, b;

	Color(float r, float g, float b) : r(r), g(g), b(b) {};
	Color() : r(0), g(0), b(0) {};
};

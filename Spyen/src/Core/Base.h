#pragma once

#define BIT(x) (1 << x)

struct Vector2 {
	float x, y;
	float Rotation;
	float Scale;

	Vector2(float x, float y, float rotation, float scale) : x(x), y(y), Rotation(rotation), Scale(scale) {};
};

struct Color {
	float r,g,b;

	Color(float r, float g, float b) : r(r), g(g), b(b) {};
};

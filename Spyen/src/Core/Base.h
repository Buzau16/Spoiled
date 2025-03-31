#pragma once
#include <glm/glm.hpp>

#define BIT(x) (1 << x)

struct Color {
	float r, g, b, a;
	//glm::vec4 color;

	Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
	Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {};
};


struct Vector2 {
	float x, y;
	Color color;


	Vector2() : x(0.0f), y(0.0f), color(0.0f, 0.0f, 0.0f, 1.0f) {}
	Vector2(float x, float y, Color color) : x(x), y(y), color(color) {}

};


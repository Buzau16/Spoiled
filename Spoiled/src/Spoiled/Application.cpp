#include <iostream>

#include <Spyen.h>

int main() {
	std::string title = "Spyen";
	uint32_t width = 800;
	uint32_t height = 600;
	Spyen::InitWindow(title, width, height);
    return 0;
}
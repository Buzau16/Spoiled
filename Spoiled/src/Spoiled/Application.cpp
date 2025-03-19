#include <iostream>

#include <Spyen/Spyen.h>

int main() {
	Spyen::InitWindow("Spyen", 800, 600);
	Spyen::SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

	Spyen::Run();
    return 0;
}
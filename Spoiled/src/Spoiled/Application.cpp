#include <iostream>
#include <Spyen.h>

int main() {
	Spyen::InitWindow("Spyen", 1600, 900);
	Spyen::SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

	Spyen::Init();
	Spyen::AddQuad({ 0.0f, 0.0f, {1.0f, 0.0f, 0.0f, 1.0f} });
	Spyen::AddQuad({ 0.5f, 0.5f, {0.0f, 1.0f, 0.0f, 1.0f} });
	Spyen::Run();
    return 0;
}
#include <iostream>
#include <Spyen.h>
#include "BoxEntity.h"

int main() {
	Spyen::InitWindow("Spyen", 1600, 900);
	Spyen::SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

	Spyen::Init();
	Spyen::AddEntity(std::make_unique<BoxEntity>());

	Spyen::Run();
    return 0;
}
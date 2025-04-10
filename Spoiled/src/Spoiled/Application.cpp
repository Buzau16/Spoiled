#include <iostream>
#include <Spyen.h>
#include "BoxEntity.h"

int main() {
	Spyen::Init("Spyen", 1600, 900);
	Spyen::AssetManager::Load<Spyen::Texture>("player", "assets/textures/player.png");
	Spyen::SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

	SPY_INFO("Love it");
	
	Spyen::AddEntity(std::make_unique<BoxEntity>());

	Spyen::Run();
    return 0;
}
#include <iostream>
#include <Spyen.h>
#include "BoxEntity.h"
#include "TextObj.h"

int main() {
	Spyen::Init("Spyen", 1600, 900);
	Spyen::AssetManager::Load<Spyen::Texture>("player", "assets/textures/player.png");
	Spyen::SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	
	Spyen::AddDynamicObject(std::make_unique<BoxEntity>());
	Spyen::AddStaticObject(std::make_unique<TextObj>());

	Spyen::Run();
    return 0;
}
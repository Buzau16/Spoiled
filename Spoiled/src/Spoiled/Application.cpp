#include <iostream>
#include <Spyen.h>
#include "BoxEntity.h"
#include "TextObj.h"
#include "TileM.h"

int main() {
	Spyen::Engine::Init("Spyen", 1600, 900);

	Spyen::AssetManager::Load<Spyen::Texture>("player", "assets/textures/player.png");

	Spyen::Engine::SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	Spyen::Scene scene;

	scene.AddObject(std::make_unique<BoxEntity>());
		for (size_t x = 0; x < 10; x++)
			scene.AddObject(std::make_unique<TextObj>(Vector2{ (float)x/10, (float)x/10}, Color{(float)x, (float)x/1, (float)x+1, 1.0f}));
	
	Spyen::Engine::AddScene(scene);
	Spyen::Engine::SetActiveScene(scene);

	Spyen::Engine::Run();
    return 0;
}
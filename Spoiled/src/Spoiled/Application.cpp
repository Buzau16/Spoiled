#include <iostream>
#include <Spyen.h>
#include "BoxEntity.h"
#include "TextObj.h"

int main() {
	Spyen::Engine::Init("Spyen", 1600, 900);

	Spyen::AssetManager::Load<Spyen::Texture>("player", "assets/textures/player.png");

	Spyen::Engine::SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	Spyen::Scene scene;
	scene.AddObject(std::make_unique<BoxEntity>());
	scene.AddObject(std::make_unique<TextObj>());
	Spyen::Engine::AddScene(std::move(scene));
	Spyen::Engine::SetActiveScene(std::move(scene));
	
	/*Spyen::Engine::AddDynamicObject(std::make_unique<BoxEntity>());
	Spyen::Engine::AddStaticObject(std::make_unique<TextObj>());*/

	Spyen::Engine::Run();
    return 0;
}
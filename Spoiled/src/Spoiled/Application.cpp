#include <iostream>
#include <Spyen.h>
#include "BoxEntity.h"
#include "TextObj.h"
#include "TileM.h"
#include "ControlObject.h"

int main() {
	Spyen::Engine::Init("Spyen", 1600, 900);


	Spyen::AssetManager::LoadTexture("player", "assets/textures/Player.png");
	Spyen::AssetManager::LoadSound("test", "assets/sounds/test.mp3");
	Spyen::AssetManager::LoadSound("step", "assets/sounds/step.mp3");
	Spyen::AssetManager::LoadSound("shot", "assets/sounds/shot.mp3");

	Spyen::Engine::SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	auto scene1 = Spyen::Scene::Create("MainScene");
	auto scene2 = Spyen::Scene::Create("SecondScene");
	Spyen::Engine::AddScene(scene1);
	Spyen::Engine::AddScene(scene2);
	Spyen::Engine::SetActiveScene("MainScene");

	//scene1->AddObject<ControlObject>("ControlObject");
	//scene2->AddObject<ControlObject>("ControlObject");
	scene1->AddObject<BoxEntity>("Player");

	Spyen::Engine::Run();
    return 0;
}

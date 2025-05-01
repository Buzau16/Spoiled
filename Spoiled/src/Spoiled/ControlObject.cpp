#include "ControlObject.h"

void ControlObject::OnCreate()
{
	Spyen::Engine::GetActiveScene()->AddObject<TextObj>(std::to_string(0).c_str());
}

void ControlObject::OnUpdate(Spyen::Timestep ts)
{
	if (Spyen::Input::IsKeyDown(Spyen::SPK_TAB)) {
		
		Spyen::Engine::GetActiveScene()->AddObject<TextObj>(std::to_string(name).c_str());
		auto obj = Spyen::Engine::GetActiveScene()->GetObjectByName(std::to_string(name).c_str());

		Spyen::Engine::GetActiveScene()->GetObjectByName(std::to_string(name).c_str())->SetPosition(r, g);
		Spyen::Engine::GetActiveScene()->GetObjectByName(std::to_string(name).c_str())->SetScale(0.1f);
		name++;
		r = std::min(r + 0.1f, 1.0f);
		g = std::min(g + 0.1f, 1.0f);
		b = std::min(b + 0.1f, 1.0f);
	}

	if (Spyen::Input::IsKeyDown(Spyen::SPK_S)) {
		SPY_INFO("Active Scene: {}", Spyen::Engine::GetActiveScene()->GetName());
		auto scene = Spyen::Engine::GetActiveScene()->GetName();
		if (scene == "MainScene") {
			Spyen::Engine::SetActiveScene("SecondScene");
			SPY_INFO("Switching scenes: MAIN -> SECOND ");
		}
		else if (scene == "SecondScene") {
			Spyen::Engine::SetActiveScene("MainScene");
			SPY_INFO("Switching scenes: SECOND -> MAIN ");
		}
	}

	if (Spyen::Input::IsKeyDown(Spyen::SPK_P)) {
		SPY_INFO("Playing sounds....");
		Spyen::SoundManager::PlaySound("test");
	}
}

void ControlObject::OnRender()
{
}

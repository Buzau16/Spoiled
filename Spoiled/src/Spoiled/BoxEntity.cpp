#include "BoxEntity.h"

void BoxEntity::OnCreate()
{
	SetPosition(0.0f, 0.0f);
	SetScale(1.0f);
	SetRotation(0.0f);
	SetColor(1.0f, 0.2f, 0.3f, 1.0f);
	SetTexture(Spyen::AssetManager::GetTexture("player"));
}

void BoxEntity::OnUpdate(Spyen::Timestep ts)
{	
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_W)) {
		m_Position.y += 1.f * ts;
		Spyen::SoundManager::PlaySound("step");
	}
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_S)) {
		m_Position.y -= 1.f * ts;
		Spyen::SoundManager::PlaySound("step");
	}
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_D)) {
		m_Position.x += 1.f * ts;
		Spyen::SoundManager::PlaySound("step");
	}
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_A)) {
		m_Position.x -= 1.f * ts;
		Spyen::SoundManager::PlaySound("step");
	}

	if (Spyen::Input::IsMouseButtonPressed(Spyen::SPMB_LEFT)) {
		Spyen::SoundManager::PlaySound("shot");
	}
}

void BoxEntity::OnRender()
{
	Spyen::Renderer::Submit(*this);
}



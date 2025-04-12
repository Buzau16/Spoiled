#include "BoxEntity.h"

void BoxEntity::OnCreate()
{
	SetPosition(0.0f, 0.0f);
	SetScale(1.0f);
	SetRotation(0.0f);
	SetColor(1.0f, 0.2f, 0.3f, 1.0f);
	SetTexture(Spyen::AssetManager::Get<Spyen::Texture>("player"));
}

void BoxEntity::OnUpdate(Spyen::Timestep ts)
{	
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_W)) {
		m_Position.y += 1.f * ts;
	}
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_S)) {
		m_Position.y -= 1.f * ts;
	}
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_D)) {
		m_Position.x += 1.f * ts;
	}
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_A)) {
		m_Position.x -= 1.f * ts;
	}
}

void BoxEntity::OnRender()
{
	Spyen::Renderer::Submit(*this);
}



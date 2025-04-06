#include "BoxEntity.h"

BoxEntity::BoxEntity()
{
	m_X = 0.0f;
	m_Y = 0.0f;
	m_Scale = 1.0f;
	m_Rotation = 0.0f;
	m_Color = { 1.0f, 0.2f, 0.3f, .5f };
}

BoxEntity::~BoxEntity()
{

}

void BoxEntity::OnUpdate(Spyen::Timestep ts)
{	
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_W)) {
		m_Y += 1.f * ts;
	}
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_S)) {
		m_Y -= 1.f * ts;
	}
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_D)) {
		m_X += 1.f * ts;
	}
	if (Spyen::Input::IsKeyPressed(Spyen::SPK_A)) {
		m_X -= 1.f * ts;
	}
}

void BoxEntity::OnRender()
{
	Spyen::Renderer::SubmitQuad({m_X, m_Y}, m_Rotation, m_Scale, m_Color);
}

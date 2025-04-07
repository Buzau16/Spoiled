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
	Spyen::Renderer::SubmitQuad(m_Position, m_Rotation, m_Scale, m_Color);
}

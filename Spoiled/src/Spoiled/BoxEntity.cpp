#include "BoxEntity.h"

BoxEntity::BoxEntity()
{
	m_X = 0.0f;
	m_Y = 0.0f;
	m_Scale = 1.0f;
	m_Rotation = 0.0f;
	m_Color = { 1.0f, 1.0f, 1.0f, .5f };
}

BoxEntity::~BoxEntity()
{

}

void BoxEntity::OnUpdate(Spyen::Timestep ts)
{
	m_Rotation += 10.f * ts;
}

void BoxEntity::OnRender()
{
	Spyen::Renderer::SubmitQuad({ m_X, m_Y, m_Rotation, m_Scale, m_Color });
}

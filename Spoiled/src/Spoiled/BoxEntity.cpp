#include "BoxEntity.h"

BoxEntity::BoxEntity()
{
	m_X = 0.0f;
	m_Y = 0.0f;
	m_Scale = 1.0f;
	m_Rotation = 0.0f;
	m_Color = { 1.0f, 0.2f, 0.1f, .5f };
}

BoxEntity::~BoxEntity()
{

}

void BoxEntity::OnUpdate(Spyen::Timestep ts)
{	
	m_AnimTime += ts; // Crește animtime în funcție de timpul scurs

	// Generăm o animație de scalare între 0.5 și 1.5 folosind funcția sin()
	m_Scale = 1.0f + sinf(m_AnimTime * 2.0f) * 0.5f; // Modifică valoarea de scalare într-un interval de 0.5 - 1.5

	// Rotația
	m_Rotation += 10.0f * ts; // Rotește cubul cu un unghi de 10 grade pe secundă
}

void BoxEntity::OnRender()
{
	Spyen::Renderer::SubmitQuad({ m_X, m_Y, m_Rotation, m_Scale, m_Color });
}

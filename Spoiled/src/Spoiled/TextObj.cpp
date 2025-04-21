#include "TextObj.h"

void TextObj::OnCreate()
{
	SetPosition(0.0f, 0.0f);
	SetScale(1.0f);
	SetRotation(0.0f);
	SetColor(1.0f, 0.2f, 0.3f, 1.0f);
}

void TextObj::OnRender()
{
	Spyen::Renderer::Submit(*this);
}



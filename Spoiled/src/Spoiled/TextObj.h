#pragma once
#include <Spyen.h>

class TextObj : public Spyen::StaticGameObject
{
public:
	TextObj() = default;
	TextObj(Spyen::Vector2 pos, Spyen::Color color) { SetPosition(pos); SetColor(color); SetScale(1.0f); SetRotation(0.f); };
	void OnRender() override;
	void OnCreate() override;
};


#pragma once
#include <Spyen.h>

class TextObj : public Spyen::StaticGameObject
{
public:
	TextObj() = default;
	TextObj(Vector2 pos, Color color) { SetPosition(pos); SetColor(color); SetScale(1.0f); SetRotation(0.f); };
	void OnRender() override;
	void OnCreate() override;
};


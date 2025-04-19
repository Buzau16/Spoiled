#pragma once
#include <Spyen.h>

class TextObj : public Spyen::StaticGameObject
{
public:
	TextObj() = default;
	TextObj(Vector2 pos, Color color) { SetPosition(pos); SetColor(color); };
	void OnRender() override;
	void OnCreate() override;
};


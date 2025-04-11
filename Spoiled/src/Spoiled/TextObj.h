#pragma once
#include <Spyen.h>

class TextObj : public Spyen::StaticGameObject
{
public:
	void OnRender() override;
	void OnCreate() override;
};


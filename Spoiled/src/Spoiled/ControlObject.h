#pragma once
#include <Spyen.h>
#include "TextObj.h"
#include "BoxEntity.h"
#include "GameObjects/StaticGameObject.h"
#include "Audio/SoundManager.h"

class ControlObject : public Spyen::DynamicGameObject
{
public:
	void OnCreate() override;
	void OnUpdate(Spyen::Timestep ts) override;
	void OnRender() override;
private:
	uint32_t name;
	float r = -1.f, g = -1.f, b = 0;

};


#pragma once
#include <Spyen.h>
#include <Time/Timestep.h>

class BoxEntity : public Spyen::DynamicGameObject
{
public:
	void OnUpdate(Spyen::Timestep ts) override;
	void OnRender() override;
	void OnCreate() override;

private:
	float m_AnimTime = 0.0f;
};

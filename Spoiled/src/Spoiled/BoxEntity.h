#pragma once
#include <Spyen.h>
#include <Time/Timestep.h>

class BoxEntity : public Spyen::Entity
{
public:
	BoxEntity();
	~BoxEntity();
	void OnUpdate(Spyen::Timestep ts) override;
	void OnRender() override;
};

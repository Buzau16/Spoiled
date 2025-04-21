#pragma once
#include <Spyen.h>
#include "TextObj.h"

class TileM : public Spyen::StaticGameObject
{
public:
	TileM() = default;
	void OnRender() override;
	void OnCreate() override;
private:
	std::vector<TextObj> objs;

};


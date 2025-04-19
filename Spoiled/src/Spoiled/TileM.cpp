#include "TileM.h"

void TileM::OnRender()
{

	for (size_t y = 0; y < 10; y) {
		for (size_t x = 0; x < 10; x++) {
			Spyen::Renderer::Submit(TextObj({ (float)x,(float)y }, { 1 / (float)x, 1 / (float)y, 1.f, 1.f }));
		}
	}
}

void TileM::OnCreate()
{
}

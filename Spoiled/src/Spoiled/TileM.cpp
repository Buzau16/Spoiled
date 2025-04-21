#include "TileM.h"

void TileM::OnRender()
{
	//SPY_INFO("TileM size: {0}", objs.size());
	for (size_t y = 0; y < 10; y++) {
		for (size_t x = 0; x < 10; x++) {
			objs[x + y].OnRender();
		}
	}
}

void TileM::OnCreate()
{
	for (size_t y = 0; y < 10; y++) {
		for (size_t x = 0; x < 10; x++) {
			float texX = (x == 0) ? 1.0f : 1 / (float)x;  // Evita impartirea la 0
			float texY = (y == 0) ? 1.0f : 1 / (float)y;  // Evita impartirea la 0
			objs.push_back(TextObj({ (float)x,(float)y }, { texX, texY, 1.f, 1.f }));
		}
	}
}

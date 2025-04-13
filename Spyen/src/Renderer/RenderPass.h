#pragma once
#include "Renderer/Renderable2D.h"

namespace Spyen {
	class RenderPass {
	public:
		virtual void Begin() = 0;
		virtual void Flush() = 0;
		virtual void End() = 0;
	};
}
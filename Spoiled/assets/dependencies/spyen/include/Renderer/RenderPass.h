#pragma once
#include "Renderer/Renderable2D.h"

namespace Spyen {
	class SPYEN_API RenderPass {
	public:
		virtual void Begin() = 0;
		virtual void Flush() = 0;
		virtual void End() = 0;
	};
}
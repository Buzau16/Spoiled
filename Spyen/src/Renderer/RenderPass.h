#pragma once

namespace Spyen {
	class RenderPass {
	public:
		virtual void Begin() = 0;
		virtual void Flush() = 0;
		virtual void End() = 0;
	};
}
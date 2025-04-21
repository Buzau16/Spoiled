#include "spypch.h"
#include "StaticObjectRenderPass.h"

namespace Spyen {
	void StaticObjectRenderPass::Begin()
	{
		Renderer::BeginBatch();
	}

	void StaticObjectRenderPass::Submit(const Renderable2D& obj)
	{
		SPY_CORE_ASSERT(obj.isStatic, "Trying to render a Dynamic object in a Static Object RenderPass");
		if (obj.texture) {
			Renderer::SubmitQuad(obj.transform, obj.texture);
		}
		else {
			Renderer::SubmitQuad(obj.transform, obj.color);
		}
	}

	void StaticObjectRenderPass::Flush()
	{
		Renderer::Flush();
	}
	void StaticObjectRenderPass::End()
	{
		Renderer::EndBatch();
	}
}

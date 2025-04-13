#include "spypch.h"
#include "DynamicObjectRenderPass.h"

namespace Spyen {
	void DynamicObjectRenderPass::Begin()
	{
		Renderer::BeginBatch();
	}
	void DynamicObjectRenderPass::Submit(const Renderable2D& obj)
	{
		SPY_CORE_ASSERT(!obj.isStatic, "Trying to render a static object in a Dynamic Object RenderPass");
		if (obj.texture) {
			Renderer::SubmitQuad(obj.transform, obj.texture);
		}
		else {
			Renderer::SubmitQuad(obj.transform, obj.color);
		}
	}

	void DynamicObjectRenderPass::Flush()
	{
		Renderer::Flush();
	}
	void DynamicObjectRenderPass::End()
	{
		Renderer::EndBatch();
	}
}
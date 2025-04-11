#include "spypch.h"
#include "DynamicObjectRenderPass.h"

namespace Spyen {
	void DynamicObjectRenderPass::Begin()
	{
		Renderer::BeginBatch();
	}
	void DynamicObjectRenderPass::Submit(const DynamicGameObject& obj)
	{
		if (obj.GetTexture()) {
			Renderer::SubmitQuad(obj.GetPosition(), obj.GetRotation(), obj.GetScale(), obj.GetTexture());
			return;
		}
		else {
			Renderer::SubmitQuad(obj.GetPosition(), obj.GetRotation(), obj.GetScale(), obj.GetColor());
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
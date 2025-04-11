#include "spypch.h"
#include "StaticObjectRenderPass.h"

namespace Spyen {
	void StaticObjectRenderPass::Begin()
	{
		Renderer::BeginBatch();
	}
	void StaticObjectRenderPass::Submit(const StaticGameObject& obj)
	{
		if (obj.GetTexture()) {
			Renderer::SubmitQuad(obj.GetPosition(), obj.GetRotation(), obj.GetScale(), obj.GetTexture());
			return;
		}
		else {
			Renderer::SubmitQuad(obj.GetPosition(), obj.GetRotation(), obj.GetScale(), obj.GetColor());
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

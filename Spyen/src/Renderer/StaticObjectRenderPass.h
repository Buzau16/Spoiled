#pragma once
#include "Renderer/RenderPass.h"
#include "Renderer/Renderer.h"
#include "GameObjects/StaticGameObject.h"

namespace Spyen {
	class StaticObjectRenderPass : RenderPass
	{
	public:
		StaticObjectRenderPass() = default;
		~StaticObjectRenderPass() = default;

		void Begin() override;
		void Submit(const Renderable2D& obj);;
		void Flush() override;
		void End() override;

		static std::shared_ptr<StaticObjectRenderPass> Create() {
			return std::make_shared<StaticObjectRenderPass>();
		}
	};

}
#pragma once
#include "Renderer/RenderPass.h"
#include "Renderer/Renderer.h"
#include "GameObjects/DynamicGameObject.h"

namespace Spyen {
    class SPYEN_API DynamicObjectRenderPass : RenderPass {
    public:
        DynamicObjectRenderPass() = default;
        ~DynamicObjectRenderPass() = default;

        void Begin() override;
        void Submit(const Renderable2D& obj);
        void Flush() override;
        void End() override;

        static std::shared_ptr<DynamicObjectRenderPass> Create() {
            return std::make_shared<DynamicObjectRenderPass>();
        }
    };
} // namespace Spyen
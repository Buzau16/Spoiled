#pragma once
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Texture.h"
#include "GameObjects/StaticGameObject.h"
#include "GameObjects/DynamicGameObject.h"
#include "Renderer/DynamicObjectRenderPass.h"
#include "Renderer/StaticObjectRenderPass.h"
#include "Input/Input.h"
#include "glm/glm.hpp"

namespace Spyen {
	class SPYEN_API Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginBatch();
		static void EndBatch();
		static void Flush();

		static void BeginFrame();
		static void EndFrame();
		static void Submit(const StaticGameObject& obj);
		static void Submit(const DynamicGameObject& obj);

		static void SubmitQuad(const Vector2& vect);
		static void SubmitQuad(const Vector2& vect, float rotation);
		static void SubmitQuad(const Vector2& vect, float rotation, float scale);
		static void SubmitQuad(const Vector2& vect, float rotation, float scale, Color color);
		static void SubmitQuad(const Vector2& vect, float rotation, float scale, const std::shared_ptr<Texture>& texture);
		static void SubmitQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture);
		static void SubmitQuad(const glm::mat4& transform, Color color);

	private:
		static void ToggleWireframe();
	};

}
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

namespace Spyen {
	class Renderer
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

	private:
		static void ToggleWireframe();
	};

}
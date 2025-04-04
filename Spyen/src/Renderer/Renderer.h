#pragma once
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Texture.h"

namespace Spyen {
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginBatch();
		static void EndBatch();
		static void Flush();

		static void SubmitQuad(const Vector2& vect);
		static void SubmitQuad(const Vector2& vect, float rotation);
		static void SubmitQuad(const Vector2& vect, float rotation, float scale);
		static void SubmitQuad(const Vector2& vect, float rotation, float scale, Color color);
		static void SubmitQuad(const Vector2& vect, float rotation, float scale, const std::shared_ptr<Texture>& texture);
	};

}
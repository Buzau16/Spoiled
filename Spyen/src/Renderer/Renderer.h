#pragma once
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

namespace Spyen {
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginBatch();
		static void EndBatch();
		static void SubmitQuad(const Vector2& position, const Color& color);
		static void Flush();
	};

}
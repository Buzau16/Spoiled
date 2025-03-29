#pragma once
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"

namespace Spyen {
	class Renderer
	{
	public:
		static void Init();
		static void BeginBatch();
		static void EndBatch();
		static void Flush();
		static void Shutdown();
		static void SubmitQuad(Vector2 vect, Color color);
	};
}


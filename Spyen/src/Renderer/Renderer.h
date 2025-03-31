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
		static void AddQuad(const Vector2& vect) { s_QuadVertices.push_back(vect); };
		static void SubmitQuad(const Vector2& vect);
		static void Flush();

		static std::vector<Vector2> s_QuadVertices;
	};

}
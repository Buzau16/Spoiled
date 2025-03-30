#include "spypch.h"
#include "Renderer.h"


namespace Spyen {

	struct QuadVertex {
		glm::vec2 Position;
		glm::vec4 Color;
	};

	struct RendererData {
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<VertexBuffer> QuadVertexBuffer;
		std::shared_ptr<IndexBuffer> QuadIndexBuffer;
		std::shared_ptr<Shader> QuadShader;

		QuadVertex* QuadVertexBufferBase;
		QuadVertex* QuadVertexBufferPtr;
		uint32_t QuadIndexCount = 0;

		glm::vec2 QuadPositions[4];

	};

	static RendererData s_Data;

	void Renderer::Init() {
		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
		s_Data.QuadVertexArray = VertexArray::Create();
		s_Data.QuadVertexArray->Bind();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(nullptr, s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->Bind();
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float2, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadPositions[0] = { -0.5f, -0.5f };
		s_Data.QuadPositions[1] = { 0.5f, -0.5f };
		s_Data.QuadPositions[2] = { 0.5f, 0.5f };
		s_Data.QuadPositions[3] = { -0.5f, 0.5f };

		uint32_t* indices = new uint32_t[s_Data.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;
			offset += 4;
		}

		s_Data.QuadIndexBuffer = IndexBuffer::Create(indices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->AddIndexBuffer(s_Data.QuadIndexBuffer);
		delete[] indices;


		s_Data.QuadShader = Shader::Create("QuadShader", "C:/Users/gpro9/source/repos/SPOILED/bin/Debug-windows-x86_64/Spoiled/assets/shaders/QuadShader.vert", "C:/Users/gpro9/source/repos/SPOILED/bin/Debug-windows-x86_64/Spoiled/assets/shaders/QuadShader.frag");
	}

	void Renderer::Shutdown() {
		glDeleteVertexArrays(1, &s_Data.QuadVertexArray->GetRendererID());
		glDeleteBuffers(1, &s_Data.QuadVertexBuffer->GetRendererID());
		glDeleteBuffers(1, &s_Data.QuadIndexBuffer->GetRendererID());


		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer::BeginBatch() {
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.QuadIndexCount = 0;
	}

	void Renderer::EndBatch() {
		GLsizeiptr size = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, size);
		Flush();
	}

	void Renderer::Flush() {
		s_Data.QuadShader->Bind();
		s_Data.QuadVertexArray->Bind();
		glDrawElements(GL_TRIANGLES, s_Data.QuadIndexCount, GL_UNSIGNED_INT, nullptr);
		s_Data.QuadIndexCount = 0;
	}

	void Renderer::SubmitQuad(const Vector2& position, const Color& color) {
		if (s_Data.QuadIndexCount >= RendererData::MaxIndices) {
			EndBatch();
			Flush();
			BeginBatch();
		}

		glm::vec4 col = { color.r, color.g, color.b, 1.0f };

		for (int i = 0; i < 4; i++) {
			s_Data.QuadVertexBufferPtr->Position = s_Data.QuadPositions[i];
			s_Data.QuadVertexBufferPtr->Color = col;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;
	}

}	

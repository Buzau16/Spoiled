#include "spypch.h"
#include "Renderer.h"
#include "Texture.h" // Add this include to define TextureSpecs
#include <filesystem>

namespace Spyen {

	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		uint32_t TexIndex;
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
		std::shared_ptr<Texture> WhiteTexture;

		QuadVertex* QuadVertexBufferBase;
		QuadVertex* QuadVertexBufferPtr;
		uint32_t QuadIndexCount = 0;

		glm::vec4 QuadPositions[4];
		std::array<std::shared_ptr<Texture>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 is reserved for white texture

	};

	static RendererData s_Data;

	void Renderer::Init() {
		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
		s_Data.QuadVertexArray = VertexArray::Create();
		s_Data.QuadVertexArray->Bind();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(nullptr, s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->Bind();
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		s_Data.QuadPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

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

		s_Data.WhiteTexture = Texture::Create(TextureSpecs());
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (int i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		s_Data.QuadShader = Shader::Create("QuadShader", "assets/shaders/QuadShader.vert", "assets/shaders/QuadShader.frag");


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

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);
	}

	void Renderer::Flush() {
		s_Data.QuadShader->Bind();
		s_Data.QuadVertexArray->Bind();
		glDrawElements(GL_TRIANGLES, s_Data.QuadIndexCount, GL_UNSIGNED_INT, nullptr);
		s_Data.QuadIndexCount = 0;
	}

	void Renderer::SubmitQuad(const Vector2& vect)
	{
		SubmitQuad(vect, 0.0f, 1.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	void Renderer::SubmitQuad(const Vector2& vect, float rotation)
	{
		SubmitQuad(vect, rotation, 1.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	void Renderer::SubmitQuad(const Vector2& vect, float rotation, float scale)
	{
		SubmitQuad(vect, rotation, scale, { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	void Renderer::SubmitQuad(const Vector2& vect, float rotation, float scale, Color color) {

		glm::vec2 textCoords[4] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};

		if (s_Data.QuadIndexCount >= s_Data.MaxIndices) {
			EndBatch();
			Flush();
			BeginBatch();
		}

		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, glm::vec3(vect.x, vect.y, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(scale, scale, 1.0f));
		
        for (int i = 0; i < 4; i++) {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadPositions[i];
            s_Data.QuadVertexBufferPtr->Color = glm::vec4(color.r, color.g, color.b, color.a);
			s_Data.QuadVertexBufferPtr->TexCoord = textCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = 0;
            s_Data.QuadVertexBufferPtr++;
        }

		s_Data.QuadIndexCount += 6;
	}

	void Renderer::SubmitQuad(const Vector2& vect, float rotation, float scale, const std::shared_ptr<Texture>& texture)
	{
		glm::vec2 textCoords[4] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};
		if (s_Data.TextureSlotIndex >= s_Data.MaxTextureSlots)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}

		if (s_Data.QuadIndexCount >= s_Data.MaxIndices) {
			EndBatch();
			Flush();
			BeginBatch();
		}

		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, glm::vec3(vect.x, vect.y, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(scale, scale, 1.0f));

		for (int i = 0; i < 4; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadPositions[i];
			s_Data.QuadVertexBufferPtr->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
			s_Data.QuadVertexBufferPtr->TexCoord = textCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = texture->GetRendererID();
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;
	}

}

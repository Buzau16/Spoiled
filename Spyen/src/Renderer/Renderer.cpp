#include "spypch.h"
#include "Renderer.h"
#include <filesystem>

namespace Spyen {

	struct QuadVertex {
		glm::vec2 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		float TexIndex;
	};

	static uint32_t s_DrawCalls = 0;

	struct RendererData {
		std::shared_ptr<StaticObjectRenderPass> StaticObjectRenderPass;
		std::shared_ptr<DynamicObjectRenderPass> DynamicObjectRenderPass;


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
		uint32_t TextureSlotIndex = 1; // 0 is the white texture used for just colors

		bool WireframeMode = false;

	};

	static RendererData s_Data;

	void Renderer::Init() {
		SPY_CORE_INFO("Initializing Renderer");

		// Creating the VAO and the buffer
		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
		s_Data.QuadVertexArray = VertexArray::Create();
		s_Data.QuadVertexArray->Bind();

		// Creating the VBO and setting the layout
		s_Data.QuadVertexBuffer = VertexBuffer::Create(nullptr, s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->Bind();
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float2, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoords"},
			{ ShaderDataType::Float, "a_TexIndex"}
			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		s_Data.QuadPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

		// Indices stuff
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

		s_Data.QuadShader = Shader::Create("QuadShader", "assets/shaders/QuadShader.vert", "assets/shaders/QuadShader.frag");

		// Creating the White Texture(1x1) if the user wants to render a color and not a texture
		s_Data.WhiteTexture = Texture::Create(TextureSpecs{ 1,1, GL_RGBA });
		uint32_t whitetx = 0xFFFFFFFF;
		s_Data.WhiteTexture->SetData(&whitetx, sizeof(uint32_t));
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
		int32_t samplers[32];
		for (size_t i = 0; i < s_Data.MaxTextureSlots; i++) {
			samplers[i] = i;
		}

		s_Data.QuadShader->Bind();
		s_Data.QuadShader->SetUniform1iv("u_Textures", s_Data.MaxTextureSlots, samplers);

		s_Data.StaticObjectRenderPass = StaticObjectRenderPass::Create();
		s_Data.DynamicObjectRenderPass = DynamicObjectRenderPass::Create();

	}

	void Renderer::Shutdown() {
		glDeleteVertexArrays(1, &s_Data.QuadVertexArray->GetRendererID());
		glDeleteBuffers(1, &s_Data.QuadVertexBuffer->GetRendererID());
		glDeleteBuffers(1, &s_Data.QuadIndexBuffer->GetRendererID());


		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer::BeginBatch() {
		// Reseting the buffer pointer for a new batch
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.QuadIndexCount = 0;
		s_Data.TextureSlotIndex = 1;
		s_DrawCalls = 0;
	}

	void Renderer::EndBatch() {
		// Sending the data in the buffer to the gpu
		GLsizeiptr size = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, size);
		for (int32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);
		Flush();
		//std::cout << "Draw Calls: " << s_DrawCalls << '\n';
	}

	void Renderer::Flush() {
		// the draw itself
		s_Data.QuadShader->Bind();
		s_Data.QuadVertexArray->Bind();
		glDrawElements(GL_TRIANGLES, s_Data.QuadIndexCount, GL_UNSIGNED_INT, nullptr);
		s_DrawCalls++;
	}

	void Renderer::BeginFrame()
	{
		ToggleWireframe();
		glPolygonMode(GL_FRONT_AND_BACK, s_Data.WireframeMode ? GL_LINE : GL_FILL);

		
		s_Data.StaticObjectRenderPass->Begin();
		s_Data.DynamicObjectRenderPass->Begin();
	}

	void Renderer::EndFrame()
	{
		
		s_Data.StaticObjectRenderPass->End();
		s_Data.DynamicObjectRenderPass->End();

		s_Data.DynamicObjectRenderPass->Flush();
		s_Data.DynamicObjectRenderPass->Flush();

		/*if (s_Data.WireframeMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}*/
	}

	void Renderer::Submit(const StaticGameObject& obj)
	{
		s_Data.StaticObjectRenderPass->Submit(obj);
	}

	void Renderer::Submit(const DynamicGameObject& obj)
	{
		s_Data.DynamicObjectRenderPass->Submit(obj);
	}

	///////////// Functions for submiting a quad to the renderer //////////////////////////
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
			s_Data.QuadVertexBufferPtr->TexCoords = textCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
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

		float textureIndex = 0.0f;

		if (s_Data.QuadIndexCount >= s_Data.MaxIndices) {
			EndBatch();
			Flush();
			BeginBatch();
		}

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++) {
			if (*s_Data.TextureSlots[i] == *texture) {
				textureIndex = static_cast<float>(i);
				break;
			}
		}

		if (s_Data.TextureSlotIndex >= s_Data.MaxTextureSlots) {
			EndBatch();
			Flush();
			BeginBatch();
		}

		if (textureIndex == 0.0f) {
			textureIndex = static_cast<float>(s_Data.TextureSlotIndex);
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, glm::vec3(vect.x, vect.y, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(scale, scale, 1.0f));

		for (int i = 0; i < 4; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadPositions[i];
			s_Data.QuadVertexBufferPtr->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
			s_Data.QuadVertexBufferPtr->TexCoords = textCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;
	}

	void Renderer::ToggleWireframe()
	{
		if (Input::IsKeyDown(SPK_TAB)) {
			if (!s_Data.WireframeMode) {
				s_Data.WireframeMode = true;
			}
			else {
				s_Data.WireframeMode = false;
			}
		}
	}

}

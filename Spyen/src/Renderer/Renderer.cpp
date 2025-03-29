#include "spypch.h"
#include "Renderer.h"


// TOD: FIX HEAP CORRUPTION

namespace Spyen {
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		/*glm::vec2 TexCoords;
		uint32_t TexIndex;*/
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


		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBuffPtr = nullptr;
		QuadVertex* QuadVertexBuff = nullptr;
		glm::vec2 QuadPosition[4];
	};

	static RendererData s_Data;

	void Renderer::Init()
	{
		s_Data.QuadVertexArray = VertexArray::Create();
		s_Data.QuadVertexBuffer = VertexBuffer::Create(nullptr, s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			/*{ ShaderDataType::Float2, "a_TexCoords" },
			{ ShaderDataType::Int, "a_TexIndex" }*/
			});

		s_Data.QuadVertexArray->BindVertexBuffer(s_Data.QuadVertexBuffer);
		s_Data.QuadVertexBuff = new QuadVertex[s_Data.MaxVertices];
		s_Data.QuadVertexBuffPtr = s_Data.QuadVertexBuff;

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			offset += 4;
		}


		s_Data.QuadIndexBuffer = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->BindIndexBuffer(s_Data.QuadIndexBuffer);
		delete[] quadIndices;

		s_Data.QuadShader = Shader::Create("QuadShader", "C:/Users/gpro9/source/repos/SPOILED/bin/Debug-windows-x86_64/Spoiled/assets/shaders/QuadShader.vert", "C:/Users/gpro9/source/repos/SPOILED/bin/Debug-windows-x86_64/Spoiled/assets/shaders/QuadShader.frag");

		if (s_Data.QuadShader == nullptr)
			std::cerr << "QuadShader is nullptr" << std::endl;

		s_Data.QuadPosition[0] = { -0.5f, -0.5f };
		s_Data.QuadPosition[1] = { 0.5f, -0.5f };
		s_Data.QuadPosition[2] = { 0.5f, 0.5f };
		s_Data.QuadPosition[3] = { -0.5f, 0.5f };
	}

	void Renderer::BeginBatch()
	{
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBuffPtr = s_Data.QuadVertexBuff;
		
	}

	void Renderer::EndBatch()
	{
		uint32_t size = (uint8_t*)s_Data.QuadVertexBuffPtr - (uint8_t*)s_Data.QuadVertexBuff;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBuff, size);
		Flush();
	}

	void Renderer::Flush()
	{
		s_Data.QuadVertexArray->Bind();
		s_Data.QuadShader->Bind();
	
		glDrawElements(GL_TRIANGLES, s_Data.QuadIndexCount, GL_UNSIGNED_INT, nullptr);

		s_Data.QuadShader->Unbind();
		s_Data.QuadVertexArray->Unbind();
	}


	void Renderer::Shutdown()
	{
		glDeleteVertexArrays(1, &s_Data.QuadVertexArray->GetRendererID());
		glDeleteBuffers(1, &s_Data.QuadVertexBuffer->GetRendererID());
		glDeleteBuffers(1, &s_Data.QuadIndexBuffer->GetRendererID());
		
		delete[] s_Data.QuadVertexBuff;

	}

	void Renderer::SubmitQuad(Vector2 vect, Color color)
	{
		//std::cout << "Submitting Quad" << std::endl;
		glm::vec3 position = { vect.x, vect.y, 0.0f };
		glm::vec4 col = { color.r, color.g, color.b, 1.0f };

		if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}

		// Calculate the position of each vertex without the model matrix
		float cosTheta = cos(glm::radians(vect.rotation));
		float sinTheta = sin(glm::radians(vect.rotation));

		for (int i = 0; i < 4; i++) {
			

			// Calculate the position of each vertex with the roation and scale
			glm::vec3 scale = { s_Data.QuadPosition[i].x * vect.scale, s_Data.QuadPosition[i].y * vect.scale, 0.0f };
			glm::vec3 rotated = { cosTheta * scale.x - sinTheta * scale.y,
								  sinTheta * scale.x + cosTheta * scale.y, 
								  0.0f };
			
			s_Data.QuadVertexBuffPtr->Position = { rotated.x + position.x, 
												   rotated.y + position.y, 0.0f };
			s_Data.QuadVertexBuffPtr->Color = col;
			float u = (i % 2) ? 1.0f : 0.0f;
			float v = (i / 2) ? 1.0f : 0.0f;
			//s_Data.QuadVertexBuffPtr->TexCoords = { u, v };
			//s_Data.QuadVertexBuffPtr->TexIndex = 0;
			s_Data.QuadVertexBuffPtr++;
		}
		s_Data.QuadIndexCount += 6;
	}
}
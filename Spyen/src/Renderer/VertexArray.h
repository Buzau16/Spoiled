#pragma once
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include <vector>
#include <memory>

namespace Spyen {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();
		void BindVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer);
		void BindIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer);

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
		static std::shared_ptr<VertexArray> Create();

		uint32_t& GetRendererID() { return m_RendererID; };
	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex;
	};
}


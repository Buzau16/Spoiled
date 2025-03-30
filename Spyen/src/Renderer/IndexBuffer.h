#pragma once

namespace Spyen {
	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t count);
		~IndexBuffer();
		void Bind() const;
		void Unbind() const;
		uint32_t GetCount() const { return m_Count; }
		static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);
		uint32_t& GetRendererID() { return m_RendererID; }
	
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}


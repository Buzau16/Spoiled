#pragma once
#include "Texture/stb_image.h"
#include "Texture/Texture.h"

namespace Spyen {
	class Texture
	{
	public:
		Texture(const std::string& filepath);
		~Texture();

		void Bind(uint32_t slot);
		void SetData(void* data, uint32_t size);
		uint32_t GetTextureID() { return m_TextureID; };
	private:
		int32_t m_Width, m_Height, m_BitDepth;
		uint32_t m_TextureID;
	};
}

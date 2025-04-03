#include "spypch.h"
#include "Texture.h"

namespace Spyen {
	Texture::Texture(const std::string& filepath)
	{
		unsigned char* data = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BitDepth, 0);
		assert(data, "Failed to load Texture: " + filepath);


		GLenum format = (m_BitDepth == 4) ? GL_RGBA : GL_RGB;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, format, m_Width, m_Height);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TextureID);
	}
	void Texture::Bind(uint32_t slot)
	{
		glBindTextureUnit(slot, m_TextureID);
	}
	void Texture::SetData(void* data, uint32_t size)
	{
		GLenum format = (m_BitDepth == 4) ? GL_RGBA : GL_RGB;
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);
	}
}

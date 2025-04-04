#include "spypch.h"
#include "Texture.h"

namespace Spyen {
	Texture::Texture(const std::string& path)
	{
		unsigned char* data = stbi_load(path.c_str(), &m_Specs.Width, &m_Specs.Height, &m_Specs.BitDepth, 4);
		if (!data) {
			assert(data, "Failed to load texture: " + path);
			return;
		}
		m_Specs.Format = (m_Specs.BitDepth == 4) ? GL_RGBA : GL_RGB;
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_Specs.Format, m_Specs.Width, m_Specs.Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Specs.Width, m_Specs.Height, m_Specs.Format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(m_RendererID);

		stbi_image_free(data);
	}

	Texture::Texture(const TextureSpecs& specs)
	{
		m_Specs = specs;
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_Specs.Format, m_Specs.Width, m_Specs.Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void Texture::Unbind(uint32_t slot) const
	{
		glBindTextureUnit(slot, 0);
	}

	void Texture::SetData(void* data, uint32_t size)
	{
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Specs.Width, m_Specs.Height, m_Specs.Format, GL_UNSIGNED_BYTE, data);
	}

	std::shared_ptr<Texture> Texture::Create(const std::string& path)
	{
		return std::make_shared<Texture>(path);
	}

	std::shared_ptr<Texture> Texture::Create(const TextureSpecs& specs)
	{
		return std::make_shared<Texture>(specs);
	}
}

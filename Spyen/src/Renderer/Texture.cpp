#include "spypch.h"
#include "Texture.h"

namespace Spyen {
	Texture::Texture(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path.c_str(), &m_Specs.Width, &m_Specs.Height, &m_Specs.BitDepth, 0);
		if (!data) {
			SPY_CORE_ERROR("Failed to load texture: {0}. Using a Fallback Texture. Check if the file is in the specified directory and for any typos", path);

			m_Specs.Width = 1;
			m_Specs.Height = 1;
			m_Specs.BitDepth = 4;
			data = (unsigned char*)malloc(4);
			data[0] = 0xf3;
			data[1] = 0x05;
			data[2] = 0xf7;
			data[3] = 0xff;
		}

		m_InternalFormat = (m_Specs.BitDepth == 4) ? GL_RGBA8 : GL_RGB8;
		m_DataFormat = (m_Specs.BitDepth == 4) ? GL_RGBA : GL_RGB;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Specs.Width, m_Specs.Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Specs.Width, m_Specs.Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

		GLenum error = glGetError();
		SPY_CORE_ASSERT(error == GL_NO_ERROR, "Error in Texture creation with code: {0}", error);

		if (data) {
			if (stbi_failure_reason()) {
				free(data);
			}
			else {
				stbi_image_free(data);
			}
		}
	}

	Texture::Texture(const TextureSpecs& specs)
	{
		m_Specs = specs;
		m_InternalFormat = (m_Specs.BitDepth == 4) ? GL_RGB8 : GL_RGBA8;
		m_DataFormat = (m_Specs.BitDepth == 4) ? GL_RGB : GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Specs.Width, m_Specs.Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		GLenum error = glGetError();
		SPY_CORE_ASSERT(error == GL_NO_ERROR, "Error in Texture creation with code: {0}", error);
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

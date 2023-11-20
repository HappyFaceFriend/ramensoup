#include "pch.h"
#include "OpenGLTexture2D.h"

#include "stb_image.h"

namespace Ramensoup
{

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, ImageFormat format)
		:m_Width(width), m_Height(height)
	{
		SetFormat(format);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);	//levels = mipmap size

		//TODO : These should be taken as parameters`
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: OpenGLTexture2D(std::move(std::string(path)))
	{
	}
	OpenGLTexture2D::OpenGLTexture2D(std::string&& path)
		:m_Path(std::move(path))
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data;
		{
			data = stbi_load(m_Path.c_str(), &width, &height, &channels, 0);
		}
		RS_CORE_ASSERT(data, "Failed to load image {0}", m_Path);

		m_Width = width;
		m_Height = height;

		m_DataFormat = 0;
		if (channels == 4)
		{
			SetFormat(ImageFormat::RGBA8);
		}
		else if (channels == 3)
		{
			SetFormat(ImageFormat::RGB8);
		}

		RS_CORE_ASSERT(m_InternalFormat && m_DataFormat, "Image format not supported");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);	//levels = mipmap size

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::SetFormat(ImageFormat format)
	{
		if (format == ImageFormat::RGBA8)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}
		else if (format == ImageFormat::RGB8)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}
		else if (format == ImageFormat::Depth24Stencil8)
		{
			m_InternalFormat = GL_DEPTH24_STENCIL8;
			m_DataFormat = GL_RGBA;
		}
		else
			RS_CORE_ASSERT(false, "Unknown image format");
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::SetData(const void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA8 ? 4 : 3;
		RS_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}
}
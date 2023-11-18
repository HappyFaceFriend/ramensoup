#pragma once

#include <glad/glad.h>

#include "Ramensoup/Renderer/Texture.h"


namespace Ramensoup
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height, ImageFormat format);
		virtual ~OpenGLTexture2D() override;

		OpenGLTexture2D(const OpenGLTexture2D&) = delete;
		OpenGLTexture2D(OpenGLTexture2D&&) = delete;
		OpenGLTexture2D& operator=(const OpenGLTexture2D&) = delete;
		OpenGLTexture2D& operator=(OpenGLTexture2D&&) = delete;

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

		virtual void SetData(const void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		inline uint32_t GetRendererID() const { return m_RendererID; }
	private:
		void SetFormat(ImageFormat format);
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat; //shader sample format
	};
}
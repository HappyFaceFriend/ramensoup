#pragma once

#include "Ramensoup/Renderer/Texture.h"

#include <glad/glad.h>

namespace Ramensoup
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		[[nodiscard]] OpenGLTexture2D(const std::string& path);
		[[nodiscard]] OpenGLTexture2D(std::string&& path);
		[[nodiscard]] OpenGLTexture2D(uint32_t width, uint32_t height, ImageFormat format);
		~OpenGLTexture2D() override;

		OpenGLTexture2D(const OpenGLTexture2D&) = delete;
		OpenGLTexture2D(OpenGLTexture2D&&) = delete;
		OpenGLTexture2D& operator=(const OpenGLTexture2D&) = delete;
		OpenGLTexture2D& operator=(OpenGLTexture2D&&) = delete;

		[[nodiscard]] bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

		void Bind(uint32_t slot = 0) const override;

		void SetData(const void* data, uint32_t size) override;

		[[nodiscard]] uint32_t GetWidth() const override { return m_Width; }
		[[nodiscard]] uint32_t GetHeight() const override { return m_Height; }

		[[nodiscard]] inline uint32_t GetRendererID() const { return m_RendererID; }

	private:
		const std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat = 0, m_DataFormat = 0; //shader sample format

	private:
		void SetFormat(ImageFormat format);
	};
}
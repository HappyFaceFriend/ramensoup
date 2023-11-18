#pragma once

#include "Ramensoup/Renderer/FrameBuffer.h"
#include "OpenGLTexture2D.h"

namespace Ramensoup
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();

		OpenGLFrameBuffer(const OpenGLFrameBuffer&) = delete;
		OpenGLFrameBuffer(OpenGLFrameBuffer&&) = delete;
		OpenGLFrameBuffer& operator=(const OpenGLFrameBuffer&) = delete;
		OpenGLFrameBuffer& operator=(OpenGLFrameBuffer&&) = delete;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		enum class AttachmentType { Color, Depth };
	public:
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_Attachments.at("color")->GetRendererID(); }

	private:
		void ReallocateAttachments();
		void OpenGLFrameBuffer::AddAttachment(const std::string& name, AttachmentType type, ImageFormat format);
	private:
		uint32_t m_RendererID = 0;
		std::unordered_map<std::string, std::unique_ptr<OpenGLTexture2D>> m_Attachments;
		FrameBufferSpecification m_Specification;
	};
}
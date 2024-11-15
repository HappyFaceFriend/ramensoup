#include "pch.h"
#include "OpenGLFrameBuffer.h"

namespace Ramensoup
{
	//These should be checked by GPU spec
	static constexpr uint32_t MAX_FRAMEBUFFER_SIZE = 8192;

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec)
	{
		glCreateFramebuffers(1, &m_RendererID);
		ReallocateAttachments();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}
	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > MAX_FRAMEBUFFER_SIZE || height > MAX_FRAMEBUFFER_SIZE)
		{
			RS_CORE_LOG_WARN("Attempted to resize framebuffer to {0}, {1}", width, height);
			return;
		}
		m_Specification.Width = width;
		m_Specification.Height = height;
		ReallocateAttachments();
	}

	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void OpenGLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void OpenGLFrameBuffer::AddAttachment(const std::string& name, AttachmentType type, ImageFormat format)
	{
		m_Attachments[name] = std::make_unique<OpenGLTexture2D>(m_Specification.Width, m_Specification.Height, format);
		//TODO : Need to enable multiple color attachments (currently only using zero)
		if (type == AttachmentType::Color)
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Attachments[name]->GetRendererID(), 0);
		else if (type == AttachmentType::Depth)
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_Attachments[name]->GetRendererID(), 0);
	}
	void OpenGLFrameBuffer::ReallocateAttachments()
	{
		if (m_RendererID)
		{
			m_Attachments.clear();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		AddAttachment("color", AttachmentType::Color, ImageFormat::RGBA8);
		AddAttachment("depth", AttachmentType::Depth, ImageFormat::Depth24Stencil8);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		RS_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
	}
}
#pragma once

namespace Ramensoup
{
	struct FrameBufferSpecification
	{
		uint32_t Width = 1280, Height = 720;
		//FramebufferFormat format;
		uint32_t Samples = 1;

		bool SwapChainTarget = false; //glBindFramebuffer(0) (unbind all buffers)
	};
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpecification& spec);
	};
}
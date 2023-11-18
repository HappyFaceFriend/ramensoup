#pragma once

namespace Ramensoup
{
	class RenderContext
	{
	public:
		virtual ~RenderContext() = default;

		RenderContext() = default;
		RenderContext(const RenderContext&) = delete;
		RenderContext(RenderContext&&) = delete;
		RenderContext& operator=(const RenderContext&) = delete;
		RenderContext& operator=(RenderContext&&) = delete;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		
	};
}
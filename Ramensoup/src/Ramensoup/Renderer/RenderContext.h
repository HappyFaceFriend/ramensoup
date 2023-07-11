#pragma once

namespace Ramensoup
{
	class RenderContext
	{
	public:
		virtual ~RenderContext() {}
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		
	};
}
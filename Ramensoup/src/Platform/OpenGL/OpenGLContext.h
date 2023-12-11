#pragma once

#include "Ramensoup/Renderer/RenderContext.h"

#ifdef RS_PLATFORM_WINDOWS
	#pragma warning(push)
	#pragma warning(disable:4819)
	#include <GLFW/glfw3.h>
	#pragma warning(pop)
#endif

namespace Ramensoup
{
	class OpenGLContext : public RenderContext
	{
	private:
#ifdef RS_PLATFORM_WINDOWS
		using NativeWindow = GLFWwindow;
#endif 
	public:
		[[nodiscard]] OpenGLContext(NativeWindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;

	private:
		NativeWindow* const m_WindowHandle;
	};
}
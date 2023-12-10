#pragma once

#include "Ramensoup/Renderer/RenderContext.h"


#ifdef RS_PLATFORM_WINDOWS
struct GLFWwindow;
typedef GLFWwindow NativeWindow;
#endif 


namespace Ramensoup
{
	class OpenGLContext : public RenderContext
	{
	public:
		[[nodiscard]] OpenGLContext(NativeWindow* windowHandle);
		void Init() override;
		void SwapBuffers() override;

	private:
		NativeWindow* const m_WindowHandle;
	};
}
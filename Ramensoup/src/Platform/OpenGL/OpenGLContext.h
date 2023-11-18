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
		OpenGLContext(NativeWindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		NativeWindow* m_WindowHandle;
	};
}
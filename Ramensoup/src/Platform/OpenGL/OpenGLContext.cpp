#include <pch.h>

#include "OpenGLContext.h"

#ifdef RS_PLATFORM_WINDOWS
	#include <GLFW/glfw3.h>
#endif 

#include <glad/glad.h>

#include "Ramensoup/Core/Debug.h"

namespace Ramensoup
{
	OpenGLContext::OpenGLContext(NativeWindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		RS_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		//Windows code
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RS_CORE_ASSERT(status, "Failed to initialize Glad");
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
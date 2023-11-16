#include "pch.h"

#include "OpenGLContext.h"

#ifdef RS_PLATFORM_WINDOWS
	#include <GLFW/glfw3.h>
#endif 

#include <glad/glad.h>


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

		RS_CORE_LOG_INFO("OpenGL");
		RS_CORE_LOG_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		RS_CORE_LOG_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		RS_CORE_LOG_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

#ifdef RS_ENABLE_ASSERTS
		int versionMajor, versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		RS_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 3), "Ramensoup requires OpenGL 4.3");
#endif
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
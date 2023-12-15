#include "pch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Ramensoup
{
	const std::shared_ptr<Shader> Shader::Create(const zstring_view& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::API::OpenGL:
			return std::shared_ptr<Shader>(new OpenGLShader(filePath));
		}
		RS_CORE_ASSERT(false, "Unknwon RendererAPI");
		return nullptr;
	}

	size_t Shader::GetDataTypeSize(DataType type)
	{
		switch (type)
		{
		case DataType::Float:		return 4;
		case DataType::Float2:	return 4 * 2;
		case DataType::Float3:	return 4 * 3;
		case DataType::Float4:	return 4 * 4;
		case DataType::Mat3:		return 4 * 3 * 3;
		case DataType::Mat4:		return 4 * 4 * 4;
		case DataType::Int:		return 4;
		case DataType::Int2:		return 4 * 2;
		case DataType::Int3:		return 4 * 3;
		case DataType::Int4:		return 4 * 4;
		case DataType::Bool:		return 1;
		}
		RS_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}
}
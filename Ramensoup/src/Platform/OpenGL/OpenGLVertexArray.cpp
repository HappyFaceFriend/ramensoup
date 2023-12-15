#include "pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Ramensoup
{
	static GLenum ShaderDataTypeToOpenGLBaseType(Shader::DataType type)
	{
		switch (type)
		{
		case Shader::DataType::Float:		return GL_FLOAT;
		case Shader::DataType::Float2:	return GL_FLOAT;
		case Shader::DataType::Float3:	return GL_FLOAT;
		case Shader::DataType::Float4:	return GL_FLOAT;
		case Shader::DataType::Mat3:		return GL_FLOAT;
		case Shader::DataType::Mat4:		return GL_FLOAT;
		case Shader::DataType::Int:		return GL_INT;
		case Shader::DataType::Int2:		return GL_INT;
		case Shader::DataType::Int3:		return GL_INT;
		case Shader::DataType::Int4:		return GL_INT;
		case Shader::DataType::Bool:		return GL_BOOL;
		}
		RS_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		RS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type)
				, element.Normalized ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), reinterpret_cast<const void*>(element.Offset));
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}
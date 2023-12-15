#pragma once

#include "Shader.h"

namespace Ramensoup
{
	class BufferLayout;

	class VertexBuffer
	{
	public:
		[[nodiscard]] VertexBuffer() = default;
		virtual ~VertexBuffer() {}

		[[nodiscard]] VertexBuffer(const VertexBuffer&) = delete;
		[[nodiscard]] VertexBuffer(VertexBuffer&&) = delete;
		[[nodiscard]] VertexBuffer& operator=(const VertexBuffer&) = delete;
		[[nodiscard]] VertexBuffer& operator=(VertexBuffer&&) = delete;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		[[nodiscard]] virtual const BufferLayout& GetLayout() const = 0;

		[[nodiscard]] static const std::shared_ptr<VertexBuffer> Create(const void* data, size_t size);
		//static const std::shared_ptr<VertexBuffer> Create(uint32_t size);
	};


	struct BufferElement
	{
		Shader::DataType Type;
		uint64_t Offset;
		size_t Size;
		bool Normalized;

		BufferElement() = default;
		BufferElement(Shader::DataType type,bool normalized = false)
			: Type(type), Size(0), Offset(0), Normalized(normalized)
		{
			Size = Shader::GetDataTypeSize(type);
		}


		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case Shader::DataType::Float:		return 1;
			case Shader::DataType::Float2:		return 2;
			case Shader::DataType::Float3:		return 3;
			case Shader::DataType::Float4:		return 4;
			case Shader::DataType::Mat3:		return 3 * 3;
			case Shader::DataType::Mat4:		return 4 * 4;
			case Shader::DataType::Int:			return 1;
			case Shader::DataType::Int2:		return 2;
			case Shader::DataType::Int3:		return 3;
			case Shader::DataType::Int4:		return 4;
			case Shader::DataType::Bool:		return 1;
			}

			RS_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;

		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
			}
			m_Stride = offset;
		}
	};
}
#pragma once

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

	enum class ShaderDataType : uint8_t
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};


	struct BufferElement
	{
		ShaderDataType Type;
		uint64_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType type,bool normalized = false)
			: Type(type), Size(0), Offset(0), Normalized(normalized)
		{
			Size = ShaderDataTypeSize(type);
		}

		static uint32_t ShaderDataTypeSize(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;
			}
			RS_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
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

		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};
}
#pragma once

namespace Ramensoup
{
	class IndexBuffer
	{
	public:
		[[nodiscard]] IndexBuffer() = default;
		virtual ~IndexBuffer() = default;

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		IndexBuffer& operator=(IndexBuffer&&) = delete;

	public:
		[[nodiscard]] static const std::shared_ptr<IndexBuffer> Create(const uint32_t* indicies, size_t count);

	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual size_t GetCount() const = 0;

	};
}
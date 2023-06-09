#pragma once

namespace Ramensoup
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static const std::shared_ptr<IndexBuffer> Create(const uint32_t* indicies, uint32_t count);
	};
}
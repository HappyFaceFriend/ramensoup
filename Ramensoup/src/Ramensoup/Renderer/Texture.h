#pragma once

#include "Defs.h"

namespace Ramensoup
{
	class Texture
	{
	public:
		[[nodiscard]] Texture() = default;
		virtual ~Texture() = default;

		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture& operator=(Texture&&) = delete;

		virtual bool operator==(const Texture& other) const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void SetData(const void* data, uint32_t size) = 0;

		[[nodiscard]] virtual uint32_t GetWidth() const = 0;
		[[nodiscard]] virtual uint32_t GetHeight() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;

	public:
		[[nodiscard]] static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height, ImageFormat format);
		[[nodiscard]] static std::shared_ptr<Texture2D> Create(const std::string& path);
		[[nodiscard]] static std::shared_ptr<Texture2D> Create(std::string&& path);
	};
}
#pragma once

#include "Texture.h"

#include <glm/glm.hpp>

namespace Ramensoup
{
	class Shader
	{
	public:
		enum class DataType : uint8_t
		{
			None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool, Texture2D
		};

		[[nodiscard]] Shader() = default;
		virtual ~Shader() = default;

		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) = delete;

		[[nodiscard]] static const std::shared_ptr<Shader> Create(const zstring_view& filePath);

		[[nodiscard]] static size_t GetDataTypeSize(DataType type);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		[[nodiscard]] virtual const std::string& GetName() const = 0;

		
		//virtual void UploadUniformBuffer

		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& values) = 0;
		virtual void SetUniformFloat3(const std::string& name, const glm::vec3& values) = 0;
		virtual void SetUniformFloat2(const std::string& name, const glm::vec2& values) = 0;
		virtual void SetUniformFloat1(const std::string& name, float value) = 0;
		virtual void SetUniformInt(const std::string& name, int value) = 0;
		virtual void SetUniformIntArray(const std::string& name, int* values, int count) = 0;
		virtual void SetTexture(const std::string& name, const std::shared_ptr<Texture2D>& texture) = 0;
	};
}
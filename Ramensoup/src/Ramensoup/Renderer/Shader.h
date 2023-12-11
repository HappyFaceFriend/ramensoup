#pragma once

#include <glm/glm.hpp>

namespace Ramensoup
{
	class Shader
	{
	public:
		[[nodiscard]] Shader() = default;
		virtual ~Shader() = default;

		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) = delete;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		[[nodiscard]] virtual const std::string& GetName() const = 0;

		[[nodiscard]] static const std::shared_ptr<Shader> Create(const zstring_view& filePath);
		[[nodiscard]] static const std::shared_ptr<Shader> Create(const std::string_view& name, const std::string_view& vertexSrc, const std::string_view& fragmentSrc);

		//virtual void UploadUniformBuffer
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& values) = 0;
		virtual void SetUniformFloat3(const std::string& name, const glm::vec3& values) = 0;
		virtual void SetUniformFloat2(const std::string& name, const glm::vec2& values) = 0;
		virtual void SetUniformFloat1(const std::string& name, float value) = 0;
		virtual void SetUniformInt(const std::string& name, int value) = 0;
		virtual void SetUniformIntArray(const std::string& name, int* values, int count) = 0;
	};
}
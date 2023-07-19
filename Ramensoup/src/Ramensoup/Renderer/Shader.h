#pragma once

#include <glm/glm.hpp>

namespace Ramensoup
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;


		virtual const std::string& GetName() const = 0;

		static const std::shared_ptr<Shader> Create(const std::string& filePath);
		static const std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		//virtual void UploadUniformBuffer
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& values) = 0;
		virtual void SetUniformFloat3(const std::string& name, const glm::vec3& values) = 0;
		virtual void SetUniformFloat2(const std::string& name, const glm::vec2& values) = 0;
		virtual void SetUniformFloat1(const std::string& name, float value) = 0;
		virtual void SetUniformInt(const std::string& name, int value) = 0;
		virtual void SetUniformIntArray(const std::string& name, int* values, int count) = 0;

	private:
	};
}
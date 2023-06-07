#pragma once

namespace Ramensoup
{
	class Window
	{
	public:
		Window(const std::string& title = "New Window", uint32_t width = 1280, uint32_t height = 720);
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		virtual ~Window();

		void OnUpdate();

		void SetVSync(bool enable);
		bool IsVSync() const;

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }


	private:
		std::string m_Title;
		uint32_t m_Width, m_Height;
		bool m_VSyncEnabled;
	};
}
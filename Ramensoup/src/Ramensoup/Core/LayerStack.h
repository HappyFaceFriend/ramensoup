#pragma once

#include "Ramensoup/Core/Layer.h"

namespace Ramensoup
{
	class LayerStack
	{
	public:
		using Iterator = std::vector<std::shared_ptr<Layer>>::iterator;
		using ConstIterator = std::vector<std::shared_ptr<Layer>>::const_iterator;

	public:
		[[nodiscard]] LayerStack() = default;

		~LayerStack();
		LayerStack(const LayerStack&) = delete;
		LayerStack(LayerStack&&) = delete;
		LayerStack& operator=(const LayerStack&) = delete;
		LayerStack& operator=(LayerStack&&) = delete;

		void PushLayer(const std::shared_ptr<Layer>& layer);
		void PushOverlay(const std::shared_ptr<Layer>& overlay);

		void PopLayer(const std::shared_ptr<Layer>& layer);
		void PopOverlay(const std::shared_ptr<Layer>& overlay);

		inline Iterator begin() { return m_Layers.begin(); }
		inline Iterator end() { return m_Layers.end(); }

		inline ConstIterator begin() const { return m_Layers.begin(); }
		inline ConstIterator end() const { return m_Layers.end(); }
				
		inline ConstIterator cbegin() const { return m_Layers.cbegin(); }
		inline ConstIterator cend() const { return m_Layers.cend(); }

	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		uint32_t m_LayerInsertIndex = 0;
	};
}
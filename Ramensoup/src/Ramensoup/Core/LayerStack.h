#pragma once

#include "Ramensoup/Core/Layer.h"

namespace Ramensoup
{
	class LayerStack
	{
	public:
		using Iterator = std::vector<Layer*>::iterator;
		using ConstIterator = std::vector<Layer*>::const_iterator;
	public:
		[[nodiscard]] LayerStack() = default;
		~LayerStack();

		LayerStack(const LayerStack&) = delete;
		LayerStack(LayerStack&&) = delete;
		LayerStack& operator=(const LayerStack&) = delete;
		LayerStack& operator=(LayerStack&&) = delete;

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline Iterator begin() { return m_Layers.begin(); }
		inline Iterator end() { return m_Layers.end(); }

		inline ConstIterator begin() const { return m_Layers.begin(); }
		inline ConstIterator end() const { return m_Layers.end(); }
				
		inline ConstIterator cbegin() const { return m_Layers.cbegin(); }
		inline ConstIterator cend() const { return m_Layers.cend(); }

		
	private:
		std::vector<Layer*> m_Layers;
		uint32_t m_LayerInsertIndex = 0;
	};
}
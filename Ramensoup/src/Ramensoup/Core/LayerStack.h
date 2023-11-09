#pragma once

#include "Ramensoup/Core/Layer.h"

namespace Ramensoup
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }

		inline std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		inline std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }

		inline std::vector<Layer*>::const_iterator cbegin() const { return m_Layers.cbegin(); }
		inline std::vector<Layer*>::const_iterator cend() const { return m_Layers.cend(); }

		template <typename T>
		void HandleEvent(T& e)
		{
			for (auto iter = cend(); iter != cbegin(); )
			{
				iter--;
				bool handled = (*iter)->HandleEvent(e);
				if (handled)
					break;
			}
		}
		
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}
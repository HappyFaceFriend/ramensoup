#include "pch.h"
#include "Layer.h"

namespace Ramensoup
{
	Layer::Layer(std::string&& name)
		: m_DebugName(std::move(name))
	{}

}
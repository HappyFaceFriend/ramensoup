#include "pch.h"
#include "Scene.h"

#include "Entity.h"

#include "Components.h"

namespace Ramensoup
{
	Entity Scene::CreateEntity(const zstring_view& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>(name);
		return entity;
	}


	void Scene::OnUpdate()
	{

	}
}
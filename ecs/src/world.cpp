#include "..\include\ecs\world.h"

#include"../include/ecs/entity.h"

using namespace bear;

bear::ecs::World::World()
{
}

void bear::ecs::World::create(std::string a_ID)
{
	m_EntityList.push_back(std::make_shared<ecs::Entity>(a_ID));
}

void bear::ecs::World::remove(std::string a_ID)
{
}

void bear::ecs::World::clear()
{
}

std::weak_ptr<ecs::Entity> bear::ecs::World::getEntity(std::string a_ID)
{
	for (std::shared_ptr<ecs::Entity> entity : m_EntityList) {
		if (entity->getID() == a_ID) {
			return entity;
		}
	}
}

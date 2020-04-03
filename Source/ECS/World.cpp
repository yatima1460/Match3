#include "World.hpp"

#include <tuple>



Entity World::CreateEntity()
{
    
}

void World::AttachComponent(Entity e, Component* c)
{
    const auto tuple = std::tuple<Entity, Component*>(e,c);
    world.push_back(tuple);
}
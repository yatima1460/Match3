#pragma once


#include "Components/Component.hpp"
#include <vector>
#include "Entity.hpp"

class World
{

    std::vector<std::tuple<Entity, Component*>> world;


public:
    Entity CreateEntity();

    
    void AttachComponent(Entity entity, Component* thing);

    template <class T>
    std::vector<T*> GetAllComponentsOfType()
    {
        return std::vector<T*>();
    }

    template <class... Types>
    std::vector<std::tuple<Types*...>> GetAllComponentsOfTypes()
    {
        return std::vector<std::tuple<Types*...>>();
    }
  
};
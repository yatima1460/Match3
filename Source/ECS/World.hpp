#pragma once


#include "Component.hpp"
#include <vector>
#include "Entity.hpp"

class World
{

public:
    Entity CreateEntity();

    
    void AttachComponent(Entity entity, Component& thing);

    template <class T>
    std::vector<T> GetAllWithComponentType(T c);
  
};
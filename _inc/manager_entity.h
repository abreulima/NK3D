#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <entity.h>
#include <vector>
#include <cstdint>

class EntityManager
{
    public:
        inline static int32_t id = 0;
        std::vector<Entity> entities;

        void add_entity(Entity e)
        {
            entities.emplace_back(e);
            id++;
        }

        std::vector<Entity>& get_entities()
        {
            return entities;
        }
};


#endif


#include "systems.h"
#include <entity.h>
#include <components.h>
#include <systems.h>

void MovementSystem::update(KEngine *k, float dt, std::vector<Entity>& entities)
{
    for (auto& entity : entities)
    {
        if (entity.is_active &&
            entity.has_component<Transform>() &&
            entity.has_component<Velocity>()
        )
        {
            //auto& transform = entity.get_component<Transform>();
            //auto& velocity = entity.get_component<Velocity>();
            //transform.x += velocity.dx * dt;
            //transform.y += velocity.dy * dt;
        }
    }
}

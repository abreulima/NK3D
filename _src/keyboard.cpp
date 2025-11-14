#include <SDL3/SDL_scancode.h>
#include <systems.h>
#include <components.h>
#include <SDL3/SDL.h>
#include <kengine.h>

void KeyboardSystem::update(KEngine *k, float dt, std::vector<Entity>& entities)
{
    for (auto& entity : entities)
    {
        if (entity.is_active &&
            entity.has_component<Keyboard>() &&
            entity.has_component<Transform>() &&
            entity.has_component<Velocity>()
        )
        {
            auto& transform = entity.get_component<Transform>();

            if (k->key_state[SDL_SCANCODE_LEFT])
                transform.position.x -= 0.1f;

            if (k->key_state[SDL_SCANCODE_RIGHT])
                transform.position.x += 0.1f;

            if (k->key_state[SDL_SCANCODE_UP])
                transform.position.z -= 0.1f;

            if (k->key_state[SDL_SCANCODE_DOWN])
                transform.position.z += 0.1f;
            //auto& velocity = entity.get_component<Velocity>();
            //transform.x += velocity.dx * dt;
            //transform.y += velocity.dy * dt;
        }
    }
}

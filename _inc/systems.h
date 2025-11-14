#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <entity.h>
#include <vector>
#include <kengine.h>

class System
{
    public:
        virtual ~System() = default;
};

class MovementSystem : public System
{
    public:
        static void update(KEngine *k, float dt, std::vector<Entity>& entities);
};

class SystemRender : public System
{
    public:
        static void update(KEngine *k, float dt, std::vector<Entity>& entities);
};

class KeyboardSystem : public System
{
    public:
        static void update(KEngine *k, float dt, std::vector<Entity>& entities);
};

#endif

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <entity.h>
#include <vector>

class System
{
    public:
        virtual void update(float dt, std::vector<Entity>& entities) = 0;
        virtual ~System() = default;
};

class MovementSystem : public System
{
    public:
        void update(float dt, std::vector<Entity>& entities) override;
};

class SystemRender : public System
{
    public:
        void update(float dt, std::vector<Entity>& entities) override;
};

#endif

#ifndef KENGINE_H
#define KENGINE_H

#include "manager_mesh.h"
#include <emscripten.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <entity.h>
#include <manager_entity.h>
#include <manager_shader.h>

// Systems
#include <systems.h>

class KEngine
{
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_GLContext gl_context;
        SDL_Event event;
        bool is_running;
        EntityManager entityManager;
        ManagerMesh manager_mesh;
        ManagerShader manager_shader;
        void Start();
        void Render();
        void EmscriptLoop();
        void End();
        void Level();

        // Systems
        MovementSystem movement_system;
        SystemRender system_render;
};

#endif

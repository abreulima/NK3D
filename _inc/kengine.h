#ifndef KENGINE_H
#define KENGINE_H

#if __EMSCRIPTEN__
    #include <emscripten.h>
    #include <SDL3/SDL.h>
    #include <SDL3/SDL_opengles2.h>  // Use ES headers for Emscripten
#else
    #include <GL/glew.h>
    #include <SDL3/SDL.h>
    #include <SDL3/SDL_opengl.h>
#endif

#include <map>

#include <entity.h>
#include <manager_entity.h>
#include <manager_shader.h>
#include <manager_mesh.h>

class KEngine
{
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_GLContext gl_context;
        SDL_Event event;
        std::map<SDL_Scancode, bool> key_state;
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
};

#endif

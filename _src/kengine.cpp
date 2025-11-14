#include "manager_shader.h"
#include "systems.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <cstdio>
#include <kengine.h>
#include <entity.h>
#include <components.h>


void KEngine::Start()
{

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error: %s", SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    this->window = SDL_CreateWindow(
        "Hello",
        800,
        600,
        SDL_WINDOW_OPENGL
    );

    if (!window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error: %s", SDL_GetError());
    }

    this->gl_context = SDL_GL_CreateContext(this->window);
    if (!this->gl_context)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error: %s", SDL_GetError());
    }

    glewExperimental = GL_TRUE; // recommended for core profile
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        printf("GLEW init error: %s\n", glewGetErrorString(err));
    }

    this->is_running = true;
    std::printf("Game is running...\n");
    Level();
}

void KEngine::Render()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            is_running = false;
        else if (event.type == SDL_EVENT_KEY_DOWN)
            key_state[event.key.scancode] = true;
        else if (event.type == SDL_EVENT_KEY_UP)
            key_state[event.key.scancode] = false;
    }

    if (key_state[SDL_SCANCODE_ESCAPE])
        is_running = false;

    // Draw Logic?
    // Perhaps another method... we will see
    //
    //movement_system.update(0.25f, entityManager.get_entities());

    KeyboardSystem::update(this, 0.25f, entityManager.get_entities());

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_MULTISAMPLE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SystemRender::update(this, 0.25f, entityManager.get_entities());
    SDL_GL_SwapWindow(this->window);
}

void KEngine::Level()
{

    auto basic = manager_shader.load_shader_from_file("basic", "_res/shaders/basic.vs.glsl", "_res/shaders/basic.fs.glsl");
    auto fox = manager_mesh.load_mesh_from_file("fox", "_res/models/fox.obj");
    auto cube = manager_mesh.load_mesh_from_file("cube", "_res/models/cube.obj");
    auto girl = manager_mesh.load_mesh_from_file("girl", "_res/models/girl.obj");

    Entity camera;
    entityManager.add_entity(camera);

    Entity player;
    player.add_component<Player>();
    player.add_component<Keyboard>();
    player.add_component<Transform>(0.0f, 0.0f, 0.0f);
    player.add_component<Velocity>();
    player.add_component<Mesh>(fox);
    player.add_component<Shader>(basic);

    Entity obj_two;
    obj_two.add_component<Transform>(1.0f, 0.5f, 5.0f);
    obj_two.add_component<Velocity>();
    obj_two.add_component<Mesh>(cube);
    obj_two.add_component<Shader>(basic);


    Entity girl_e;
    girl_e.add_component<Transform>(2.0f, 0.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    girl_e.add_component<Velocity>();
    girl_e.add_component<Mesh>(girl);
    girl_e.add_component<Shader>(basic);

    entityManager.add_entity(obj_two);
    entityManager.add_entity(player);
    entityManager.add_entity(girl_e);
    entityManager.add_entity(camera);
}

void KEngine::End()
{
    SDL_GL_DestroyContext(this->gl_context);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

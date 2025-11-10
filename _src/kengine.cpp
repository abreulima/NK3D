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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    this->gl_context = SDL_GL_CreateContext(this->window);
    if (!this->gl_context)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error: %s", SDL_GetError());
    }

    this->is_running = true;
    Level();
    std::printf("Game is running...\n");
}

void KEngine::Render()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            is_running = false;
    }

    // Draw Logic?
    // Perhaps another method... we will see
    //
    movement_system.update(0.25f, entityManager.get_entities());

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    system_render.update(0.25f, entityManager.get_entities());
    SDL_GL_SwapWindow(this->window);
}

void KEngine::Level()
{

    const std::vector<float> square_vertices = {
        // Positions (x, y, z)    // Texture coords (u, v)
        -0.5f, -0.5f, 0.0f,      // Bottom-left
         0.5f, -0.5f, 0.0f,       // Bottom-right
         0.5f,  0.5f, 0.0f,         // Top-right
        -0.5f,  0.5f, 0.0f,       // Top-left
    };

    const std::vector<unsigned int> square_indices = {
        0, 1, 2,  // First triangle
        2, 3, 0   // Second triangle
    };

    manager_mesh.load_mesh_data("square",
                           square_vertices.data(),
                           square_vertices.size(),
                           square_indices.data(),
                           square_indices.size());

    const char *vertex = R""""(#version 300 es
    precision mediump float;
    layout (location = 0) in vec3 aPos; // the position variable has attribute position 0

    out vec4 vertexColor; // specify a color output to the fragment shader

    void main()
    {
        gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
        vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
    })"""";

    const char *frag = R"""(#version 300 es
    precision mediump float;
    out vec4 FragColor;

    in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)

    void main()
    {
        FragColor = vertexColor;
    })""";

    const char *vertexShaderSource = {
        "#version 300 es\n"
        "in vec4 position;\n"
        "void main(void) {\n"
        "  gl_Position = vec4(position.xyz, 1.0);\n"
        "}\n"
    };

    const char *fragmentShaderSource = {
        "#version 300 es\n"
        "precision mediump float;\n"
        "out vec4 fragColor;\n"
        "void main(void) {\n"
        "  fragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n"
    };

    manager_shader.load_shader("basic", vertexShaderSource, fragmentShaderSource);

    Entity player;
    player.add_component<Transform>();
    player.add_component<Velocity>();
    player.add_component<Shader>(manager_shader.get_shader("basic"), "basic");
    player.add_component<Mesh>(manager_mesh.get_mesh_data("square"), "square");

    entityManager.add_entity(player);
}

void KEngine::End()
{
    SDL_GL_DestroyContext(this->gl_context);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

#include <kengine.h>

void emscripten_loop(void * arg)
{
    KEngine *engine;
    engine = (KEngine *)arg;

    if (!engine->is_running)
    {
        emscripten_cancel_main_loop();
        engine->End();
        return ;
    }

    engine->Render();
}

int main()
{
    KEngine engine;
    engine.Start();

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(emscripten_loop, (void *)&engine, 0, 1);
    #else
    while (engine.is_running) { engine.Render(); };
    #endif

    engine.End();
}

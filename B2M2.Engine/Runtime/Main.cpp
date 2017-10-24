#include <Platform/Window.hpp>
#include <Platform/Runtime.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Renderer2D.hpp>

#undef main

int main() {
    using namespace b2m2;

    cRuntime::Initalize();

    cWindow window;
    window.Create({ 800, 600, "B2M2 Engine!" });
    
    cShader *shader = cShaderManager::CreateShader(
        "Shaders/vertex.shader", "Shaders/fragment.shader"
    );

    cRenderer2D renderer;
    renderer.Initalize(shader);

    while (window.IsRunning()) {
        window.PollEvents();

        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.Begin();
        renderer.FillRectangle({ -0.5f, -0.5f }, 1.f, 1.f, { 1.0f, 0.f, 0.f, 1.f });

        renderer.End();
        renderer.Present();

        window.SwapBuffers();
    }

    window.Destroy();
    cRuntime::Shutdown();
    return 0;
}
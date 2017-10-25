#include <Platform/Window.hpp>
#include <Platform/Runtime.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Renderer2D.hpp>
#include <Graphics/Texture2D.hpp>
#include <glm/gtx/quaternion.hpp>

#undef main

int main() {
    using namespace b2m2;

    cRuntime::Initalize();

    cWindow window;
    window.Create({ 800, 600, "B2M2 Engine!" });
    
    cShader *shader = cShaderManager::CreateShaderFromFile(
        "Shaders/vertex.shader", "Shaders/fragment.shader"
    );

    cRenderer2D renderer;
    renderer.Initalize(shader, glm::ortho(0.f, 800.f, 600.f, 0.f, 1.f, -1.f));

    cTexture2D texture2d;
    texture2d.Create("Assets/spr_basicfall.png", cTexture2D::eFiltering::Nearest);

    float xPos = 0.f;
    while (window.IsRunning()) {
        window.PollEvents();

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        xPos += 1.f;
        
        renderer.Begin();

        renderer.DrawTexture(&texture2d, { 300, 300 });
        
        mat4 rotate = glm::translate(vec3(400, 300, 0)) * glm::rotate(glm::radians(xPos), glm::vec3(0, 0, 1)) * glm::translate(vec3(-400, -300, 0));

        renderer.PushTransform(rotate);
        renderer.FillRectangle({ 350, 250 }, 100, 100, { .4f, .5f, .6f, 1.f });
        renderer.FillRectangle({ 350, 250 }, 100, 100, { 1.f, 0.f, 0.f, 1.f });
        renderer.PopTransform();

        renderer.End();
        renderer.Present();

        window.SwapBuffers();
    }

    window.Destroy();
    cRuntime::Shutdown();
    return 0;
}
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
    
    cRenderer2D renderer;
    renderer.Initalize(glm::ortho(0.f, 800.f, 600.f, 0.f, 1.f, -1.f));

    cTexture2D basicFallTexture;
    basicFallTexture.Create("Assets/spr_basicfall.png", cTexture2D::eFiltering::Nearest);

    cTexture2D spritesheetTexture;
    spritesheetTexture.Create("Assets/spr_basicidle_strip5.png", cTexture2D::eFiltering::Nearest);

    cFont font;
    font.Create("Assets/WendyOne-Regular.ttf", 48);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    float xPos = 0.f;
    while (window.IsRunning()) {
        window.PollEvents();

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        xPos += 1.f;
        
        renderer.Begin();

        renderer.PushTransform(glm::scale(vec3(4, 4, 0)));
        
        renderer.DrawTexture(&basicFallTexture, { 0, 0 });
        renderer.DrawTextureClip(&spritesheetTexture, { basicFallTexture.GetWidth() + 32, 0 }, sRectangle(0, 0, 47, 16));
        
        renderer.PopTransform();
        mat4 rotate = glm::translate(vec3(400, 300, 0)) * glm::rotate(glm::radians(xPos), glm::vec3(0, 0, 1)) * glm::translate(vec3(-400, -300, 0));

        renderer.PushTransform(rotate);
        renderer.FillRectangle({ 350, 250 }, 100, 100, { .4f, .5f, .6f, 1.f });
        renderer.PopTransform();
        renderer.FillRectangle({ 350, 250 }, 100, 100, { 1.f, 0.f, 0.f, 1.f });
        
        std::string txt = "Hello World (Bob)!\nThis is a new line";
        vec2 sizes = font.MeasureString(txt);
        renderer.DrawString(txt, &font, { 400-(sizes.x/2), (300-(sizes.y/2))+200 }, vec4(.5f, .6f, 0.7f, 1.f));
        
        renderer.End();
        renderer.Present();

        window.SwapBuffers();
    }

    window.Destroy();
    cRuntime::Shutdown();
    return 0;
}
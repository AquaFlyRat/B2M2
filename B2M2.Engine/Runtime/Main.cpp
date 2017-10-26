#include <Platform/Window.hpp>
#include <Platform/Runtime.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Renderer2D.hpp>
#include <Graphics/Texture2D.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Graphics/Transform.hpp>

#include <Runtime/Animation/Spritesheet.hpp>

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

    cFont font;
    font.Create("Assets/WendyOne-Regular.ttf", 48);
    
    cSpritesheet spritesheet;
    spritesheet.Create("Assets/spr_basicrun_strip8.png", 16, 16);

    float rectangleAngle = 0.f;
    
    while (window.IsRunning()) {
        window.PollEvents();

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rectangleAngle += 1.f;
        
        renderer.Begin();

        renderer.PushTransform(glm::scale(vec3(4, 4, 0)));
        
        renderer.DrawTexture(&basicFallTexture, { 0, 0 });
        spritesheet.AnimateRow(&renderer, 0, { (400 - ((16 * 4) / 2)) / 4, 50 / 4 }, 125.f);

        renderer.PopTransform();
        
        renderer.PushTransform(cTransform::RotateAroundPoint(vec3(400, 300, 0.f), rectangleAngle));

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
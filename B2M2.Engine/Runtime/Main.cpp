#include <Platform/Window.hpp>
#include <Platform/Runtime.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Renderer2D.hpp>
#include <Graphics/Texture2D.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Graphics/Transform.hpp>
#include <Input/Keyboard.hpp>
#include <Windows.h>
#include <Runtime/Animation/Spritesheet.hpp>
#include <Box2D/Box2D.h>

#undef main

enum class AnimationState {
    Running, Idle
};

std::string text = "Type your text here...";

bool _isWireframe = false;

void onKeyDown(SDL_Event evt) {
    if (evt.key.keysym.scancode == SDL_SCANCODE_F5) {
        _isWireframe = !_isWireframe;
        if (_isWireframe) {
            glDisable(GL_BLEND);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glEnable(GL_BLEND);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    if (evt.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
        if(text.length() > 0)
            text.pop_back();
        return;
    }

    if (evt.key.keysym.scancode == SDL_SCANCODE_RETURN) {
        text.push_back('\n');
        return;
    }

    char c = b2m2::cKeyboard::GetASCIIChar(evt.key);
    if (c > 0) {
        text += c;
    }
}

#if !defined(_DEBUG)
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
#else
    int main()
#endif
{
    using namespace b2m2;
    cRuntime runtime;
    runtime.Initalize();
    
    cWindow window;
    window.Create({ 800, 600, "B2M2 Engine!" });
    window.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    window.SetKeyDownCallback(onKeyDown);

    cRenderer2D renderer;
    renderer.Initalize(glm::ortho(0.f, 800.f, 600.f, 0.f, 1.f, -1.f));

    cTexture2D basicFallTexture;
    basicFallTexture.Create("Assets/spr_basicfall.png", cTexture2D::eFiltering::Nearest);

    cFont font;
    font.Create("Assets/WendyOne-Regular.ttf", 48);
    
    cSpritesheet spritesheet;
    spritesheet.Create("Assets/player.png", 16, 16);
    cKeyboard::Initalize();

    float rectangleAngle = 0.f;
    float spriteX = (400 - ((16 * 4) / 2)) / 4;

    AnimationState state = AnimationState::Idle;
    while (window.IsRunning()) {
        window.PollEvents();
        window.Clear();

        rectangleAngle += 1.f;
        
        renderer.Begin();

        renderer.DrawString("Use <RIGHT> & <LEFT> to move", &font, { (400 - ((16 * 4) / 2)) - 300, 60 }, vec4(.5f, .6f, .7f, 1.f));
        renderer.DrawString("Quads: " + std::to_string(renderer.GetQuadCount()), &font, { 5, 5 }, { .2f,.3f,.5f,1.f });

        renderer.PushTransform(glm::scale(vec3(4, 4, 0)));   
        renderer.DrawTexture(&basicFallTexture, { 30, 300/4-16/2 });

        if (cKeyboard::IsKeyDown(SDL_SCANCODE_RIGHT)) {
            if (state != AnimationState::Running) {
                state = AnimationState::Running;
                spritesheet.ResetAnimations();
            }
            spriteX += 1.f;
            spritesheet.AnimateRow(&renderer, 0, { spriteX, 50 / 4 }, 125.f);
        }
        else if (cKeyboard::IsKeyDown(SDL_SCANCODE_LEFT)) {
            if (state != AnimationState::Running) {
                state = AnimationState::Running;
                spritesheet.ResetAnimations();
            }
            spriteX -= 1.f;
            renderer.PushTransform(cTransform::FlipHorizontal({ spriteX, 50 / 4, 0.f }, 16));
            spritesheet.AnimateRow(&renderer, 0, { spriteX, 50 / 4 }, 125.f);
            renderer.PopTransform();
        }
        else {
            if (state != AnimationState::Idle) {
                state = AnimationState::Idle;
                spritesheet.ResetAnimations();
            }
            spritesheet.AnimateRow(&renderer, 1, { spriteX, 50 / 4 }, 125.f, 5);
        }

        renderer.PopTransform();
        
        renderer.PushTransform(cTransform::RotateAroundPoint(vec3(400, 300, 0.f), rectangleAngle));
        renderer.FillRectangle({ 350, 250 }, 100, 100, { .4f, .5f, .6f, 1.f });
        renderer.PopTransform();

        renderer.FillRectangle({ 350, 250 }, 100, 100, { 1.f, 0.f, 0.f, 1.f });
        
        std::string txt = "Hello World (Bob)!\nThis is a new line";
        vec2 sizes = font.MeasureString(txt);
        
        renderer.DrawString(txt, &font,
            { 400 - (sizes.x / 2), (300 - (sizes.y / 2)) + 200 }, vec4(.5f, .6f, 0.7f, 1.f));
        renderer.DrawString(text, &font, { 50, 150 }, { 1.f, 1.f, 0.f, 1.f });
        renderer.End();
        renderer.Present();

        window.SwapBuffers();
    }

    window.Destroy();
    
    runtime.Shutdown();

    return 0;
}

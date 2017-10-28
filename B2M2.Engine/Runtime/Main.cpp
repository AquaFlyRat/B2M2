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
#include <Runtime/Scene/Scene.hpp>
#include <Runtime/CoreComponents/PhysicsComponent.hpp>

#undef main

enum class AnimationState {
    Running, Idle, Falling
};

static void AddGameObjects(b2m2::cGameObject *ground, b2m2::cGameObject *player, b2m2::cScene *scene) {
    using namespace b2m2;
    
    player->Position = { 0.f, 0.f };
    player->Size = { 1.f, 1.f };

    cPhysicsComponent *playerPhysics = new cPhysicsComponent(false, 1.f);
    playerPhysics->SetDensity(1.f);
    playerPhysics->SetFriction(0.3f);
    player->AddComponent(playerPhysics);

    ground->Position = { -16.f, -7.f };
    ground->Size = { 32.f, 1.f };

    cPhysicsComponent *groundPhysics = new cPhysicsComponent(true, 0.f);
    groundPhysics->SetDensity(0.f);
    groundPhysics->SetFriction(0.0f);
    ground->AddComponent(groundPhysics);

    scene->AddObject(player);
    scene->AddObject(ground);
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
    cKeyboard::Initalize();
    
    cWindow window;
    window.Create({ 1280, 720, "B2M2 Engine!" });
    window.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    
    cRenderer2D renderer;
    renderer.Initalize(glm::ortho(-16.f, 16.f, 9.f, -9.f, 1.f, -1.f));

    cScene scene;
    scene.Create({ 0, -10.f });

    cGameObject *player = new cGameObject();
    cGameObject *ground = new cGameObject();
    AddGameObjects(ground, player, &scene);

    cSpritesheet playerSpritesheet;
    playerSpritesheet.Create("Assets/player.png", 16, 16);
    float playerX = 0.f;

    AnimationState state = AnimationState::Idle;
    double t = 0.0;
    double dt = 1 / 60.0;
    double frameTime = 0.f;
    double currentTime = SDL_GetTicks()/1000;
    while (window.IsRunning()) {
        window.PollEvents();
        
        scene.Update();
        window.Clear();
        
        if (cKeyboard::IsKeyDown(SDL_SCANCODE_SPACE)) {
            cPhysicsComponent *component = player->GetComponent<cPhysicsComponent>();
            if (component) {
                if (component->IsOnGround())
                {
                    b2Body *body = component->GetBody();
                    float impulse = body->GetMass()*10;
                    body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);
                }
            }
        }

        renderer.Begin();
        {           
            renderer.FillRectangle({ ground->Position.x, -ground->Position.y }, ground->Size.x, ground->Size.y, { 1.f, 0.f, 0.f, 1.f });
            cPhysicsComponent *component = player->GetComponent<cPhysicsComponent>();
            
            if (cKeyboard::IsKeyDown(SDL_SCANCODE_RIGHT)) {
                if (state != AnimationState::Running) {
                    state = AnimationState::Running;
                    playerSpritesheet.ResetAnimations();
                }
                playerX += .1f;
                cPhysicsComponent *component = player->GetComponent<cPhysicsComponent>();
                if (component) {
                    if (component->IsOnGround()) {
                        playerSpritesheet.AnimateRow(&renderer, 0, { playerX, -(player->Position.y + 1) }, 125.f, 8, { .125f, .125f });
                    }
                    else {
                        playerSpritesheet.DrawSprite(&renderer, 0, 2, { playerX, -(player->Position.y + 1) }, { .125f, .125f });
                    }
                }
            }
            else if (cKeyboard::IsKeyDown(SDL_SCANCODE_LEFT)) {
                if (state != AnimationState::Running) {
                    state = AnimationState::Running;
                    playerSpritesheet.ResetAnimations();
                }
                playerX -= .1f;
                renderer.PushTransform(cTransform::FlipHorizontal({ playerX, -(player->Position.y + 1), 0.f }, 2));
                cPhysicsComponent *component = player->GetComponent<cPhysicsComponent>();
                if (component) {
                    if (component->IsOnGround()) {
                        playerSpritesheet.AnimateRow(&renderer, 0, { playerX, -(player->Position.y + 1) }, 125.f, 8, { .125f, .125f });
                    }
                    else {
                        playerSpritesheet.DrawSprite(&renderer, 0, 2, { playerX, -(player->Position.y + 1) }, { .125f, .125f });
                    }
                }
                renderer.PopTransform();
            }
            else {
                if (state != AnimationState::Idle) {
                    state = AnimationState::Idle;
                    playerSpritesheet.ResetAnimations();
                }
                cPhysicsComponent *component = player->GetComponent<cPhysicsComponent>();
                if (component) {
                    if (component->IsOnGround()) {
                        playerSpritesheet.AnimateRow(&renderer, 1, { playerX, -(player->Position.y + 1) }, 125.f, 5, { .125f, .125f });
                    }
                    else {
                        playerSpritesheet.DrawSprite(&renderer, 1, 2, { playerX, -(player->Position.y + 1) }, { .125f, .125f });
                    }
                }
            }
        }

        renderer.End();
        renderer.Present();
        
        window.SwapBuffers();
        SDL_Delay(1000 / 60);
    }

    window.Destroy();
    
    runtime.Shutdown();

    return 0;
}

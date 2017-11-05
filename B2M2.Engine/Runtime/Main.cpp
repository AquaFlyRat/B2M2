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
    renderer.Initalize(cMatrix4::Orthographic(16.f, -16.f, -9.f, 9.f, -1.f, 1.f));

    cSpritesheet playerSpritesheet;
    
    while (window.IsRunning()) {
        window.PollEvents();
        
        window.Clear();
        renderer.Begin();
        
        renderer.PushTransform(cMatrix4::Scale(2.f));

        renderer.FillRectangle({ 0, 0 }, 1, 1, { 1.f, 0.f, 1.f, 1.f });
        renderer.PopTransform();

        renderer.End();
        renderer.Present();
        
        window.SwapBuffers();
        SDL_Delay(1000 / 60);
    }

    window.Destroy();
    
    runtime.Shutdown();

    return 0;
}

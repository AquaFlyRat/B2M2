#using <mscorlib.dll>

#include "../ManagedClass.h"
#include "../Math/Vector2.hpp"

#include <SDL2/SDL_syswm.h>

#include <Platform/Runtime.hpp>
#include <Platform/Window.hpp>
#include <Windows.h>
#include <Graphics/Renderer2D.hpp>

namespace CharlieEngine {
    public enum class WindowFlags {
        ShowOnCreate = arch::eWindowFlags::ShowOnCreate,
        Borderless = arch::eWindowFlags::Borderless,
        None = arch::eWindowFlags::None,
        PositionCentre = arch::eWindowFlags::PositionCentre,
        PositionOrigin = arch::eWindowFlags::PositionOrigin
    };

    public ref class WindowConfig {
    public:
        System::UInt32 Width;
        System::UInt32 Height;
        System::String ^Title;
        WindowFlags     Flags;

        WindowConfig(int width, int height, System::String ^title, WindowFlags flags) {
            Width = width;
            Height = height;
            Title = title;
            Flags = flags;
        }
    };

    public ref class Window : ManagedClass<arch::cWindow> {
    public:
        Window(WindowConfig^ config) {
            const char * title = (const char*) 
                System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(config->Title).ToPointer();
            arch::cRuntime runtime;
            runtime.Initalize();
            m_handle = new arch::cWindow();
            m_handle->Create({ config->Width, config->Height, title, static_cast<arch::eWindowFlags>(config->Flags) });
            arch::cRenderer2D::InitShaders();
        }

        void Delay(int ms) {
            m_handle->Delay(ms);
        }

        void PollEvents() {
            m_handle->PollEvents();
        }
        
        void SwapBuffers() {
            m_handle->SwapBuffers();
        }

        void SetClearColor(float r, float g, float b, float a) {
            m_handle->SetClearColor(r, g, b, a);
        }

        void SetViewportSize(int w, int h) {
            m_handle->SetViewportSize(w, h);
        }

        void Destroy() {
            m_handle->Destroy();
        }
        
        void Clear() {
            m_handle->Clear();
        }

        property bool IsRunning {
            bool get() { return m_handle->IsRunning(); }
        }

        System::IntPtr GetHWND() {
            return System::IntPtr(m_handle->GetWin32Handle());
        }

        void SetSize(int w, int h) {
            m_handle->SetSize(w, h);
        }

        property int Width {
            int get() { 
                int w, h;
                SDL_GetWindowSize(m_handle->Handle(), &w, &h);
                return w;
            }
        }

        property int Height {
            int get() { 
                int w, h;
                SDL_GetWindowSize(m_handle->Handle(), &w, &h);
                return h;
            }
        }

        property int GLMajor {
            int get() { return m_handle->GetGLMajorVersion(); }
        }

        property int GLMinor {
            int get() { return m_handle->GetGLMinorVersion(); }
        }

        ~Window() {
            m_handle->Destroy();

            arch::cRuntime runtime;
            runtime.Shutdown();
        }
    };
};
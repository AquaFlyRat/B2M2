#using <mscorlib.dll>
#include <Platform/Window.hpp>

#include "../ManagedClass.h"
#include <Platform/Runtime.hpp>

#include <SDL2/SDL_syswm.h>
#include <Windows.h>

namespace CharlieEngine {
    //using namespace b2m2;

    public enum class WindowFlags {
        ShowOnCreate = b2m2::eWindowFlags::ShowOnCreate,
        Borderless = b2m2::eWindowFlags::Borderless,
        None = b2m2::eWindowFlags::None,
        PositionCentre = b2m2::eWindowFlags::PositionCentre,
        PositionOrigin = b2m2::eWindowFlags::PositionOrigin
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

    public ref class Window : ManagedClass<b2m2::cWindow> {
    public:
        Window(WindowConfig^ config) {
            const char * title = (const char*) 
                System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(config->Title).ToPointer();
            b2m2::cRuntime runtime;
            runtime.Initalize();
            m_handle = new b2m2::cWindow();
            m_handle->Create({ config->Width, config->Height, title, static_cast<b2m2::eWindowFlags>(config->Flags) });
        }

        void Delay(int ms) {
            SDL_Delay(ms);
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
            SDL_SysWMinfo systemInfo;
            SDL_VERSION(&systemInfo.version);
            SDL_GetWindowWMInfo(m_handle->Handle(), &systemInfo);

            HWND handle = systemInfo.info.win.window;
            return System::IntPtr(handle);
        }

        void SetSize(int w, int h) {
            SDL_SetWindowSize(m_handle->Handle(), w, h);
            glViewport(0, 0, w, h);
        }

        property int GLMajor {
            int get() { return m_handle->GetGLMajorVersion(); }
        }

        property int GLMinor {
            int get() { return m_handle->GetGLMinorVersion(); }
        }

        ~Window() {
            m_handle->Destroy();

            b2m2::cRuntime runtime;
            runtime.Shutdown();
        }
    };
};
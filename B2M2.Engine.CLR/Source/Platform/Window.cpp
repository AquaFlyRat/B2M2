#using <mscorlib.dll>
#include <Platform/Window.hpp>

#include "../ManagedClass.h"
#include <Platform/Runtime.hpp>

namespace b2m2 {

    public ref class WindowConfig {
    public:
        System::UInt32 Width;
        System::UInt32 Height;
        System::String ^Title;

        WindowConfig(int width, int height, System::String ^title) {
            Width = width;
            Height = height;
            Title = title;
        }
    };

    public ref class Window : ManagedClass<cWindow> {
    public:
        Window(WindowConfig^ config) {
            const char * title = (const char*) 
                System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(config->Title).ToPointer();
            cRuntime runtime;
            runtime.Initalize();
            m_handle = new cWindow();
            m_handle->Create({ config->Width, config->Height, title });
        }

        void PollEvents() {
            m_handle->PollEvents();
        }
        /*
        void SwapBuffers() {
            m_handle->SwapBuffers();
        }

        void SetClearColor(float r, float g, float b, float a) {
            m_handle->SetClearColor(r, g, b, a);
        }

        void Clear() {
            m_handle->Clear();
        }*/

        property bool IsRunning {
            bool get() { return m_handle->IsRunning(); }
        }

        property int GLMajor {
            int get() { return m_handle->GetGLMajorVersion(); }
        }

        property int GLMinor {
            int get() { return m_handle->GetGLMinorVersion(); }
        }

        ~Window() {
            m_handle->Destroy();
        }
    };
};
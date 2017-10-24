#using <mscorlib.dll>
#include <Platform/Window.hpp>

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

    public ref class Window {
    private:
        b2m2::cWindow *m_nativeHandle;

    public:
        Window(WindowConfig^ config) {
            const char * title = (const char*) 
                System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(config->Title).ToPointer();

            m_nativeHandle = new cWindow();
            m_nativeHandle->Create({ config->Width, config->Height, title });
        }

        void PollEvents() {
            m_nativeHandle->PollEvents();
        }

        property bool IsRunning {
            bool get() { return m_nativeHandle->IsRunning(); }
        }

        property int GLMajor {
            int get() { return m_nativeHandle->GetGLMajorVersion(); }
        }

        property int GLMinor {
            int get() { return m_nativeHandle->GetGLMinorVersion(); }
        }

        ~Window() {
            m_nativeHandle->Destroy();
            delete m_nativeHandle;
            m_nativeHandle = nullptr;
        }
    };
};
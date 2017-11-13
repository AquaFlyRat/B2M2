/*
    @author Barney Wilks
*/

#pragma once

#include "../Common.hpp"

#include <SDL2/SDL.h>
#include <functional>

namespace b2m2 {

    enum eWindowFlags {
        ShowOnCreate,
        Borderless,
        None,
        PositionCentre,
        PositionOrigin
    };

    /// <summary>
    /// SDL Window properties 
    /// </summary>
    struct sWindowConfig {
        /// <summary>
        /// Width of the window (pixels)
        /// </summary>
        uint32 Width;

        /// <summary>
        /// Height of the window (pixels)
        /// </summary>
        uint32 Height;

        /// <summary>
        /// Title/Caption of the window
        /// </summary>
        const char * Title;

        eWindowFlags Flags;
    };

    /// <summary>
    /// Represents a window that can be drawn to or receive user input
    /// </summary>
    class cWindow {
    public:
        /// <summary>
        ///  Creates a window with the specified properties
        /// </summary>
        /// <param name="config">The configuration of the window (width, height, title) etc...</param>
        void Create(const sWindowConfig& config);

        // (TODO: This doc will need to be changed when `ShowOnCreate` is changed to `IsEmbedded`
        /// <summary>
        /// Shows the window (if it has not already been shown by the 'cWindow::Create' call.
        /// This has no effect if sWindowConfig::ShowOnCreate was set to true on create. 
        /// </summary>
        void Show();

        /// <summary>
        /// Destroys the window and frees any resources directly allocated by this object
        /// </summary>
        void Destroy();

        /// <summary>
        /// Polls the event queue and dispatches any event callbacks that have been suscribed to (keydown etc...)
        /// If a quit message is polled then <code>Window::IsRunning()</code> will return false. No immediate window
        /// destruction will be done.
        /// </summary>
        void PollEvents();

        /// <summary>
        /// Swaps the OpenGL buffers.
        /// </summary>
        void SwapBuffers();

        /// <summary>
        /// Sets the OpenGL clear color. Only needs to be called once to set the color, even in a loop. Color values should
        /// be normalized (e.g. in the range 0 -> 1)
        /// </summary>
        /// <param name="r">The red component of the clear color. Should be normalized (e.g in the range 0.f -> 1.f)</param>
        /// <param name="g">The green component of the clear color. Should be normalized (e.g in the range 0.f -> 1.f)</param>
        /// <param name="b">The blue component of the clear color. Should be normalized (e.g in the range 0.f -> 1.f)</param>
        /// <param name="a">The alpha component of the clear color. Should be normalized (e.g in the range 0.f -> 1.f)</param>
        void SetClearColor(float r, float g, float b, float a);

        /// <summary>
        /// Clears the screen (e.g. resets it to the specified clear color)
        /// </summary>
        void Clear();

        /// <summary>
        /// Sets the callback that is called when a SDL_KEYDOWN event is polled. Passing NULL as a parameter
        /// will reset any previously set callbacks.
        /// </summary>
        /// <param name="callback">Called when a SDL_KEYDOWN event is polled -> the SDL_Event parameter of the callback is the one that has been polled). NULL is a valid parameter.</param>
        void SetKeyDownCallback(void(*callback)(SDL_Event));

        void SetClickCallback(const std::function<void()>& functor);

        /// <summary>
        /// Returns the SDL_Window* created during the <code> Create(...) </code> call
        /// </summary>
        /// <return>Valid SDL_Window* pointer to the SDL display that this class wraps. Please don't free or delete yourself.</return>
        SDL_Window *Handle() const { return m_handle; }

        /// <summary>
        /// Returns whether the window is running (returns false when the users quits).
        /// </summary>
        /// <return>If the window is currently open/running.</return>
        bool        IsRunning() const { return m_bRunning; }

        bool        HasFocus() const { return m_bHasKeyFocus && m_bHasMouseFocus; }

        /// <summary>
        /// The major OpenGL version (e.g the 4 of 4.3)
        /// </summary>
        /// <return>Returns the major OpenGL version - provided by <code>glGetIntegerv(GL_MAJOR_VERSION)</code></return>
        uint32      GetGLMajorVersion() const { return m_glMajorVersion;  }

        /// <summary>
        /// The minor OpenGL version (e.g the 3 of 4.3)
        /// </summary>
        /// <return>Returns the minor OpenGL version - provided by <code>glGetIntegerv(GL_MINOR_VERSION)</code></return>
        uint32      GetGLMinorVersion() const { return m_glMinorVersion; }

        void*           FocusToOnClick = NULL;
    private:
        SDL_Window      *m_handle;
        SDL_GLContext    m_glContext;

        sWindowConfig    m_config;
        bool             m_bRunning = true;
        bool             m_bHasKeyFocus = false;
        bool             m_bHasMouseFocus = false;
        int32            m_glMajorVersion;
        int32            m_glMinorVersion;
        void(*m_keyboardInputCallback)(SDL_Event);

        std::function<void()> m_clickCallback;
    };
}
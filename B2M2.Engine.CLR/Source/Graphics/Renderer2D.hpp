#pragma once

#using <mscorlib.dll>

#include <Graphics/Renderer2D.hpp>

#include "../ManagedClass.h"

#include "../Math/Vector2.hpp"
#include "../Math/Matrix4.hpp"
#include "Texture2D.hpp"
#include "Font.hpp"

namespace CharlieEngine {
    public ref class Color {
    public:
        float R, G, B, A;

        Color(float r, float g, float b, float a) {
            R = g;
            G = g;
            B = b;
            A = a;
        }
    };

    public ref class Rectangle {
    public:
        float X, Y, Width, Height;

        Rectangle(float x, float y, float width, float height) {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }
    };

    public ref class Renderer2D : ManagedClass<b2m2::cRenderer2D> {
    public:
        Renderer2D();

        void Initalize(Matrix4^ projection);

        void FillRectangle(Vector2^ pos, float width, float height, Color^ color);

        void DrawTexture(Texture2D ^texture, Vector2 ^pos);
        void DrawTexture(Texture2D ^texture, Vector2 ^pos, Color^ color);

        void DrawTextureClip(Texture2D ^texture, Vector2 ^pos, Rectangle^ clip);
        void DrawTextureClip(Texture2D ^texture, Vector2 ^pos, Rectangle^ clip, Color^ color);

        void DrawString(System::String^ text, Font ^font, Vector2^ pos, Color ^color);

        void DrawRectangle(Vector2 ^pos, float width, float height, Color ^color);

        void Begin();
        void End();
        void Present();

        void PushTransform(Matrix4 ^matrix);
        void PushTransform(Matrix4 ^matrix, bool override);

        void PopTransform();
    };
};
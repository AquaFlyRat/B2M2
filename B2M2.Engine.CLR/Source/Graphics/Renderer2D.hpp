#pragma once

#using <mscorlib.dll>

#include <Graphics/Renderer2D.hpp>

#include "../ManagedClass.h"
#include "../Math/Vector2.hpp"

namespace b2m2 {

    public ref class Renderer2D : ManagedClass<Renderer2D> {
    public:
        void Initalize(Matrix4^ projection);

        void FillRectangle(Vector2^ pos, float width, float height, Vector4 ^color);
        void DrawTexture(Texture2D ^texture, Vector2 ^pos);
        void DrawTexture(Texture2D ^texture, Vector2 ^pos, vec4 color);

        void DrawTextureClip(Texture2D ^texture, Vector2 ^pos, Rectangle^ clip);
        void DrawTextureClip(Texture2D ^texture, Vector2 ^pos, Rectangle^ clip, Vector4 ^color);

        void DrawString(System::String^ text, Font ^font, Vector2 pos, Vector2 ^color);

        void Begin();
        void End();
        void Present();

        void PushTransform(Matrix4 ^matrix);
        void PushTransform(Matrix4 ^matrix, bool override);

        void PopTransform();
    };
};
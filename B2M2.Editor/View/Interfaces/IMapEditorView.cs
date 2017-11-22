using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CharlieEngine;
using Arch.Editor.Model;

namespace Arch.Editor.View.Interfaces
{
    public class GameObjectCreatedArgs : EventArgs
    {
        /// <summary>
        /// The position that the game object has been created at, in screen coordinates.
        /// </summary>
        public Vector2 CreatedAt { get; private set; }

        public GameObjectCreatedArgs(Vector2 createdAt)
        {
            CreatedAt = createdAt;
        }
    };

    public class LeftClickArgs : EventArgs
    {
        public Vector2 ClickedPoint { get; private set; }

        public LeftClickArgs(Vector2 clickedPos)
        {
            ClickedPoint = clickedPos;
        }
    }

    public class CameraScrollArgs : EventArgs
    {
        public Vector2 NewCursorPosition { get; private set; }

        public CameraScrollArgs(Vector2 cursorPos)
        {
            NewCursorPosition = cursorPos;
        }
    }

    public class ViewportDrawArgs : EventArgs
    {
        public Renderer2D Renderer { get; private set; }

        public ViewportDrawArgs(Renderer2D renderer)
        {
            Renderer = renderer;
        }
    }

    public interface IMapEditorView
    {
        GameObject SelectedObject { get; }
        int        ViewportWidth { get; }
        int        ViewportHeight { get; }
        Renderer2D Renderer { get; }

        event EventHandler<GameObjectCreatedArgs> OnObjectCreated;
        event EventHandler<LeftClickArgs> OnLeftClick;
        event EventHandler<CameraScrollArgs> OnCameraScroll;
        event EventHandler<ViewportDrawArgs> OnViewportDraw;
        event EventHandler OnCameraScrollStop;
    }
}

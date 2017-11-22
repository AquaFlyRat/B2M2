﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DarkUI.Docking;

using Arch.Editor.View.Native;
using Arch.Editor.Model;

using CharlieEngine;

namespace Arch.Editor.View
{
    public partial class RenderWindow : DarkDocument
    {
        public static Scene CurrentScene = new Scene();
        private CharlieEngine.Font _wendyOne;
        private Point? _lastPoint = null;
        private CharlieWindow _window = null;
        private GameObject _selectedGameObject = null;

        private void SetGameObject(GameObject obj,bool select=true)
        {
            if (obj != null)
            {
                if (select)
                    _selectedGameObject = obj;
                Properties props = Editor.GetPropertiesWindow();
                props.SetPosition(obj.Position);
            } else
            {
                Properties props = Editor.GetPropertiesWindow();
                props.SetPosition(null);
                _selectedGameObject = null;
            }
        }

        public RenderWindow()
        {
            InitializeComponent();

            DockText = "Render Window";
            _window = new CharlieWindow(Width, Height, OnCharlieDraw);
            _wendyOne = new CharlieEngine.Font("Assets/WendyOne-Regular.ttf", 48);

            _window.Panel.MouseClick += (object o, MouseEventArgs e) => {
                if (e.Button == MouseButtons.Right)
                {
                    _contextMenu.Show(Parent.PointToScreen(e.Location));
                }
                if(e.Button == MouseButtons.Left)
                {
                    var cursorPosPoint = PointToClient(Cursor.Position);
                    Vector2 cursorPos = _window.GetRenderer().UnProject(Width, Height, new Vector2(cursorPosPoint.X, cursorPosPoint.Y));
                    bool found = false;
                    foreach (GameObject obj in CurrentScene.Objects)
                    {
                        if (cursorPos.X > obj.Position.X && cursorPos.X < obj.Position.X + obj.Width)
                        {
                            if (cursorPos.Y > obj.Position.Y && cursorPos.Y < obj.Position.Y + obj.Height)
                            {
                                SetGameObject(obj);
                                found = true;
                            }
                        }
                    }

                    if(!found)
                    {
                        SetGameObject(null);
                    }
                }
            };

            _window.Panel.MouseUp += Panel_MouseUp;
            _window.Panel.MouseMove += (object o, MouseEventArgs e) => {
                if (e.Button == MouseButtons.Middle)
                {             
                    if (_lastPoint == null)
                    {
                        _lastPoint = e.Location;
                    }

                    Point lValue = _lastPoint.Value;
                    float differenceX, differenceY;
                    differenceX = e.Location.X - lValue.X;
                    differenceY = e.Location.Y - lValue.Y;
                    
                    Renderer2D renderer = _window.GetRenderer();
                    var offset = new Vector2(-differenceX, -differenceY);
                    renderer.MoveCamera(offset);

                    _lastPoint = new Point(e.Location.X, e.Location.Y);
                }
            };

            _window.Panel.Resize += RenderWindow_Resize;

            _window.Show();

            // Apparantly we need both for this to work correctly...
            // Please don't touch or all hell starts to break loose.
            Win32.SetParent(_window.NativeWindow.GetHWND(), Handle);
            Controls.Add(_window.Panel);
        }

        private void RenderWindow_Resize(object sender, EventArgs e)
        {
            _window.NativeWindow.SetViewportSize(Width, Height);
            _window.GetRenderer().SetProjection(Matrix4.Orthographic(Width, 0, 0, Height, 1.0f, -1.0f));
        }

        private void Panel_MouseUp(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Middle)
            {
                _lastPoint = null;
            }
        }

        private void OnCharlieDraw(Window window, Renderer2D renderer)
        {
            var cursorPosPoint = PointToClient(Cursor.Position);
            Vector2 cursorPos = _window.GetRenderer().UnProject(Width, Height, new Vector2(cursorPosPoint.X, cursorPosPoint.Y));
            
            foreach (GameObject obj in CurrentScene.Objects)
            {
                if (cursorPos.X > obj.Position.X && cursorPos.X < obj.Position.X + obj.Width)
                {
                    if (cursorPos.Y > obj.Position.Y && cursorPos.Y < obj.Position.Y + obj.Height)
                    {
                        renderer.DrawRectangle(obj.Position, obj.Width, obj.Height, new CharlieEngine.Color(0.4f, 0.4f, 0.7f, 1.0f));
                    }
                }

                renderer.DrawString("Testing", _wendyOne, obj.Position, new CharlieEngine.Color(0.4f, 0.7f, 0.3f, 1.0f));
            }

            if (_selectedGameObject != null)
            {
                renderer.DrawRectangle(_selectedGameObject.Position, _selectedGameObject.Width, _selectedGameObject.Height, new CharlieEngine.Color(0.4f, 0.4f, 0.7f, 1.0f));
            }
        }

        private void _insertGameObject_Click(object sender, EventArgs e)
        {
            Point clientTerms = PointToClient(Cursor.Position);

            GameObject obj = new GameObject();
            Vector2 objPos = _window.GetRenderer().UnProject(Width, Height, new Vector2(clientTerms.X, clientTerms.Y));
            obj.Position = objPos;

            SetGameObject(null);
            SetGameObject(obj, false);

            Vector2 size = _wendyOne.MeasureString("Testing");
            obj.Width = (int)size.X;
            obj.Height = (int)size.Y;
            CurrentScene.Objects.Add(obj);
        }
    }
}
 
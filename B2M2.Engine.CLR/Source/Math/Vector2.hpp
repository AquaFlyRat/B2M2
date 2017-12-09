#pragma once

#using <mscorlib.dll>
#using <system.dll>
#include <Math/Vector2.hpp>

#include "../ManagedClass.h"

namespace CharlieEngine {

    public ref class Vector2 : ManagedClass<arch::cVector2>, System::ComponentModel::INotifyPropertyChanged {
    public:
        Vector2(float x, float y);
        Vector2();
        
        property float X {
            float get() { return m_handle->X; }
            void set(float x) { 
                if (x != m_handle->X) {
                    PropertyChanged(this, gcnew System::ComponentModel::PropertyChangedEventArgs("X"));
                }
                m_handle->X = x;
            }
        }

        property float Y {
            float get() { return m_handle->Y; }
            void set(float y) { 
                if (y != m_handle->Y) {
                    PropertyChanged(this, gcnew System::ComponentModel::PropertyChangedEventArgs("Y"));
                }
                m_handle->Y = y; 
            }
        }

        virtual event System::ComponentModel::PropertyChangedEventHandler ^ PropertyChanged;
    };
};
#pragma once

#using <mscorlib.dll>
#include <Math/Vector3.hpp>

#include "../ManagedClass.h"

namespace CharlieEngine {
    
    public ref class Vector3 : ManagedClass<arch::cVector3> {
    private:
        Vector3(arch::cVector3* vecptr);
    public:
        Vector3();
        Vector3(float x, float y, float z);

        property float X {
            float get() {
                return m_handle->X;
            }

            void set(float x) {
                m_handle->X = x;
            }
        }

        property float Y {
            float get() {
                return m_handle->Y;
            }

            void set(float y) {
                m_handle->Y = y;
            }

        }
        property float Z {
            float get() {
                return m_handle->Z;
            }

            void set(float z) {
                m_handle->Z = z;
            }
        }
    };
};
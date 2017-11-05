#pragma once

namespace b2m2 {
    template <typename T>
    public ref class ManagedClass {
    protected:
        T *m_handle;

    public:
        T *GetHandle() { return m_handle; }

        ManagedClass(T *ptr) {
            m_handle = ptr;
        }

        ManagedClass() {}

        virtual ~ManagedClass()
        {
            if (m_handle != nullptr)
            {
                delete m_handle;
                m_handle = nullptr;
            }
        }

        !ManagedClass()
        {
            if (m_handle != nullptr)
            {
                delete m_handle;
                m_handle = nullptr;
            }
        }
    };
}
/*
    @author Barney Wilks
*/

#pragma once

#include <vector>

#include "../../Common.hpp"

namespace arch {
    class cScene;
    class cGameObject;
    
    struct cComponent {
        virtual void Update(cGameObject *obj) = 0;
        virtual void Create(cGameObject *obj) = 0;
    };
    
    class cGameObject {
    public:
       void Update() {
            for (cComponent *component : m_components) {
                component->Update(this);
            }
        }

       void Create() {
           for (cComponent *component : m_components) {
               component->Create(this);
           }
       }

        template <typename T, typename... Args>
        void AddComponent(Args... componentArguments) {
            T *component = new T(componentArguments...);
            m_components.push_back(component);
        }

        void AddComponent(cComponent *component) {
            m_components.push_back(component);
        }

        template <typename T>
        bool HasComponent() {
            for (cComponent *component : m_components) {
                if (typeid(component).hash_code() == typeid(T).hash_code()) {
                    return true;
                }
            }

            return false;
        }

        template <typename T>
        T *GetComponent() {
            for (cComponent *component : m_components) {
                if (typeid(*component) == typeid(T)) {
                    return (T*) component;
                }
            }

            return NULL;
        }

        void Release() {
            for (cComponent *component : m_components) {
                delete component;
                component = NULL;
            }
        }

        vec2 Position, Size;
        cScene *ParentScene;

    private:
        std::vector<cComponent*> m_components;
    };
}
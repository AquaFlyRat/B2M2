/*
    @author Barney Wilks
*/

#pragma once

#include "../../Common.hpp"

namespace b2m2 {
    class cVertexArray {
    public:
        void Bind() const { glBindVertexArray(m_id); }
        void UnBind() const { glBindVertexArray(0); }

        void Generate() {
            glGenVertexArrays(1, &m_id);
        }

        ~cVertexArray() {
            glDeleteVertexArrays(1, &m_id);
        }

    private:
        GLuint m_id;
    };
}
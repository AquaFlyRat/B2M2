/*
    @author Barney Wilks
*/

#pragma once

#include "../../Common.hpp"
#include <vector>

namespace arch {

    struct sInputAttribute {
        int32 Index;
        size_t ComponentCount;
        GLenum DataType;
        size_t Stride;
        size_t ByteOffset;
    };

    class cBuffer {
    private:
        GLenum m_arrayType;
        GLenum m_drawType;
        size_t m_dataSize;
        
        GLuint m_id;
        std::vector<sInputAttribute> m_layout;

    public:
        void Bind()   const { glBindBuffer(m_arrayType, m_id); }
        void UnBind() const { glBindBuffer(m_arrayType, 0);    }

        void Generate(GLenum arrType, size_t dataSize, void * data, GLenum drawType) {
            m_arrayType = arrType;
            m_dataSize = dataSize;
            m_drawType = drawType;

            glGenBuffers(1, &m_id);
            Bind();
            glBufferData(m_arrayType, dataSize, data, m_drawType);
            UnBind();
        }

        void AddAttribute(const sInputAttribute& attrib) {
            Bind();

            glEnableVertexAttribArray(attrib.Index);
            glVertexAttribPointer(attrib.Index, 
                attrib.ComponentCount, attrib.DataType, 
                GL_FALSE, attrib.Stride, (GLvoid*) attrib.ByteOffset
            );
        }

        template <typename T>
        T *Map() {
            Bind();
            void *data = glMapBuffer(m_arrayType, GL_WRITE_ONLY);
            T *_data = reinterpret_cast<T*>(data);
            return _data;
        }

        void ReleaseMapping() {
            Bind();
            glUnmapBuffer(m_arrayType);
        }
    };
}
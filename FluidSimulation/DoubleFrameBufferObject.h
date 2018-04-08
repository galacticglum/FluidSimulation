#pragma once

#include <GL/glew.h>
#include "FrameBufferObject.h"

struct DoubleFrameBufferObject
{
    DoubleFrameBufferObject() = default;
    DoubleFrameBufferObject(GLint textureId, GLsizei width, GLsizei height, GLenum internalFormat, GLenum format, GLenum type, GLint param);

    FrameBufferObject& GetReadBuffer() { return m_FrameBufferObjects[m_ReadFrameBufferIndex]; }
    FrameBufferObject& GetWriteBuffer() { return m_FrameBufferObjects[m_WriteFrameBufferIndex]; }

    void Swap();
private:
    FrameBufferObject m_FrameBufferObjects[2];
    int m_ReadFrameBufferIndex = 0;
    int m_WriteFrameBufferIndex = 1;
};


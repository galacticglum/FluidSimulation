#pragma once

#include <GL/glew.h>
#include "FrameBufferObject.h"

struct DoubleFrameBufferObject
{
    DoubleFrameBufferObject() = default;
    DoubleFrameBufferObject(GLint textureId, GLsizei width, GLsizei height, GLenum internalFormat, GLenum format, GLenum type, GLint param);

    FrameBufferObject& GetPrimaryFrameBuffer() { return m_PrimaryFrameBuffer; }
    FrameBufferObject& GetSecondaryFrameBuffer() { return m_SecondaryFrameBuffer; }

    void Swap();
private:
    FrameBufferObject m_PrimaryFrameBuffer;
    FrameBufferObject m_SecondaryFrameBuffer;
};


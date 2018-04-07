#include "DoubleFrameBufferObject.h"

DoubleFrameBufferObject::DoubleFrameBufferObject(const GLint textureId, const GLsizei width, const GLsizei height,
    const GLenum internalFormat, const GLenum format, const GLenum type, const GLint param)
{
    m_PrimaryFrameBuffer = FrameBufferObject(textureId, width, height, internalFormat, format, type, param);
    m_SecondaryFrameBuffer = FrameBufferObject(textureId + 1, width, height, internalFormat, format, type, param);
}

void DoubleFrameBufferObject::Swap()
{
    const FrameBufferObject temp = m_PrimaryFrameBuffer;
    m_PrimaryFrameBuffer = m_SecondaryFrameBuffer;
    m_SecondaryFrameBuffer = temp;
}

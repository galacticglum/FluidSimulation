#include "DoubleFrameBufferObject.h"

DoubleFrameBufferObject::DoubleFrameBufferObject(const GLint textureId, const GLsizei width, const GLsizei height,
    const GLenum internalFormat, const GLenum format, const GLenum type, const GLint param)
{
    m_FrameBufferObjects[m_ReadFrameBufferIndex] = FrameBufferObject(textureId, width, height, internalFormat, format, type, param);
    m_FrameBufferObjects[m_WriteFrameBufferIndex] = FrameBufferObject(textureId + 1, width, height, internalFormat, format, type, param);
}

void DoubleFrameBufferObject::Swap()
{
    const int temp = m_ReadFrameBufferIndex;
    m_ReadFrameBufferIndex = m_WriteFrameBufferIndex;
    m_WriteFrameBufferIndex = temp;
}

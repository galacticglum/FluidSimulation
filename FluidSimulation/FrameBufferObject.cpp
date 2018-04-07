#include "FrameBufferObject.h"

FrameBufferObject::FrameBufferObject(const GLint textureId, const GLsizei width, const GLsizei height, const GLenum internalFormat, const GLenum format, 
    const GLenum type, const GLint param)
{
    glActiveTexture(GL_TEXTURE0 + textureId);
    glGenTextures(1, &Texture);

    glBindTexture(GL_TEXTURE_2D, Texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, nullptr);

    glGenFramebuffers(1, &ObjectHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, ObjectHandle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture, 0);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    TextureId = textureId;
}

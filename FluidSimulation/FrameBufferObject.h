#pragma once

#include <GL/glew.h>

struct FrameBufferObject
{
    static const FrameBufferObject& Empty;

    FrameBufferObject() = default;
    FrameBufferObject(GLint textureId, GLsizei width, GLsizei height, GLenum internalFormat, GLenum format, GLenum type, GLint param);

    GLuint ObjectHandle{};
    GLuint Texture{};
    GLint TextureId{};
};


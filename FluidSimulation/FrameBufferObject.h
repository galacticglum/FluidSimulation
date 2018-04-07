#pragma once

#include <GL/glew.h>

struct FrameBufferObject
{
    FrameBufferObject() = default;
    FrameBufferObject(GLint textureId, GLsizei width, GLsizei height, GLenum internalFormat, GLenum format, GLenum type, GLint param);

    GLuint ObjectHandle{};
    GLuint Texture{};
    GLint TextureId{};
};


#include "FluidRenderer.h"
#include "Window.h"
#include "Random.h"

FluidRenderer::FluidRenderer(): m_TextureWidth(0), m_TextureHeight(0)
{
    m_ClearProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/clear.frag");
    m_DisplayProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/display.frag");
    m_SplatProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/splat.frag");
    m_AdvectionProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/advection.frag");
    m_DivergenceProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/divergence.frag");
    m_CurlProgramShader = Shader("Assets/Shaders/base,vert", "Assets/Shaders/curl.frag");
    m_VorticityProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/vorticity.frag");
    m_PressureProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/pressure.frag");
    m_GradientProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/gradient.frag");
}

void FluidRenderer::Update(float deltaTime)
{
    if(!m_SplatStack.empty())
    {
        const int size = m_SplatStack.top();
        m_SplatStack.pop();

        BatchSplats(size);
    }
}

void FluidRenderer::UpdateSplat(const Vector2f& position, const Vector2f& delta, const Vector4f& colour)
{
    Window& window = Window::Get();
    const int windowWidth = window.GetWidth();
    const int windowHeight = window.GetHeight();
    const float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

    m_SplatProgramShader.Bind();
    m_SplatProgramShader.SetUniform("target", m_VelocityFrameBufferObject.GetPrimaryFrameBuffer().TextureId);
    m_SplatProgramShader.SetUniform("aspectRatio", aspectRatio);

    const Vector2f point(position.X / windowWidth, 1.0 - position.Y / windowHeight);
    m_SplatProgramShader.SetUniform("point", point);
    m_SplatProgramShader.SetUniform("colour", { delta.X, -delta.Y, 1.0 });
    m_SplatProgramShader.SetUniform("radius", Settings.SplatRadius);
    
    Blit(m_VelocityFrameBufferObject.GetSecondaryFrameBuffer());
    m_VelocityFrameBufferObject.Swap();

    m_SplatProgramShader.SetUniform("target", m_DensityFrameBufferObject.GetPrimaryFrameBuffer().TextureId);
    m_SplatProgramShader.SetUniform("colour", colour * 0.3f);
    
    Blit(m_DensityFrameBufferObject.GetSecondaryFrameBuffer());
    m_DensityFrameBufferObject.Swap();
}

void FluidRenderer::BatchSplats(const int amount)
{
    Window& window = Window::Get();
    const int windowWidth = window.GetWidth();
    const int windowHeight = window.GetHeight();

    for (int i = 0; i < amount; ++i)
    {
        const Vector4f colour = Random::RGB(0) * 10;
        const Vector2f position = { windowWidth * Random::Value(), windowHeight * Random::Value() };
        const Vector2f delta = { 1000 * (Random::Value() - 0.5f), 1000 * (Random::Value() - 0.5f) };

        UpdateSplat(position, delta, colour);
    }
}

void FluidRenderer::InitializeFrameBuffers()
{
    Window& window = Window::Get();

    m_TextureWidth = window.GetWidth() >> Settings.TextureDownsample;
    m_TextureHeight = window.GetHeight() >> Settings.TextureDownsample;

    m_DensityFrameBufferObject = DoubleFrameBufferObject(2, m_TextureWidth, m_TextureHeight, GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT, GL_LINEAR);
    m_VelocityFrameBufferObject = DoubleFrameBufferObject(0, m_TextureWidth, m_TextureHeight, GL_RG16F, GL_RG, GL_HALF_FLOAT, GL_LINEAR);
    m_DivergenceFrameBufferObject = FrameBufferObject(4, m_TextureWidth, m_TextureHeight, GL_R16F, GL_RED, GL_HALF_FLOAT, GL_NEAREST);
    m_CurlFrameBufferObject = FrameBufferObject(5, m_TextureWidth, m_TextureHeight, GL_R16F, GL_RED, GL_HALF_FLOAT, GL_NEAREST);
    m_PressureFrameBufferObject = DoubleFrameBufferObject(6, m_TextureWidth, m_TextureHeight, GL_R16F, GL_RED, GL_HALF_FLOAT, GL_NEAREST);
}

void FluidRenderer::Blit(const FrameBufferObject& frameBufferObject)
{
    GLuint* buffers = nullptr;
    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

    const GLfloat vertices[] = { -1, -1, -1, 1, 1, 1, 1, -1 };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

    const GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject.ObjectHandle);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}

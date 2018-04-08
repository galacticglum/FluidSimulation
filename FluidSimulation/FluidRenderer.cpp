#include "FluidRenderer.h"
#include "Window.h"
#include "Random.h"

#include "Input.h"

const GLfloat FluidRenderer::s_BlitSurfaceVertices[] = { -1, -1, -1, 1, 1, 1, 1, -1 };
const GLint FluidRenderer::s_BlitSurfaceIndices[] = { 0, 1, 2, 0, 2, 3 };

FluidRenderer::FluidRenderer(): m_TextureWidth(0), m_TextureHeight(0)
{
    m_ClearProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/clear.frag");
    m_DisplayProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/display.frag");
    m_SplatProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/splat.frag");
    m_AdvectionProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/advection.frag");
    m_DivergenceProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/divergence.frag");
    m_CurlProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/curl.frag");
    m_VorticityProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/vorticity.frag");
    m_PressureProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/pressure.frag");
    m_GradientProgramShader = Shader("Assets/Shaders/base.vert", "Assets/Shaders/gradient.frag");

    InitializeFrameBuffers();
    GenerateBlitSurface();
    BatchSplats(static_cast<int>(Random::Value() * 20 + 5));
}

void FluidRenderer::Update(const float deltaTime)
{
    glViewport(0, 0, m_TextureWidth, m_TextureHeight);

    /*if(!m_SplatStack.empty())
    {
        const int size = m_SplatStack.top();
        m_SplatStack.pop();

        BatchSplats(size);
    }

    m_AdvectionProgramShader.Bind();
    m_AdvectionProgramShader.SetUniform("texelSize", Vector2f(1.0f / m_TextureWidth, 1.0f / m_TextureHeight));
    m_AdvectionProgramShader.SetUniform("velocity", m_VelocityFrameBufferObject.GetReadBuffer().TextureId);
    m_AdvectionProgramShader.SetUniform("source", m_VelocityFrameBufferObject.GetReadBuffer().TextureId);
    m_AdvectionProgramShader.SetUniform("dt", deltaTime);
    m_AdvectionProgramShader.SetUniform("dissipation", Settings.VelocityDissipation);

    Blit(m_VelocityFrameBufferObject.GetWriteBuffer());
    m_VelocityFrameBufferObject.Swap();

    m_AdvectionProgramShader.SetUniform("velocity", m_VelocityFrameBufferObject.GetReadBuffer().TextureId);
    m_AdvectionProgramShader.SetUniform("source", m_DensityFrameBufferObject.GetReadBuffer().TextureId);
    m_AdvectionProgramShader.SetUniform("dissipation", Settings.DensityDissipation);

    Blit(m_DensityFrameBufferObject.GetWriteBuffer());
    m_DensityFrameBufferObject.Swap();
    
    if(Input::GetMouseButton(MouseButton::MOUSE_BUTTON_LEFT))
    {
        const Vector2f mousePosition = Input::GetMousePosition();

        const Vector2f direction((mousePosition - m_PreviousMousePosition) * 10.0f);
        const Vector4f colour = Random::RGB(0) * 0.2f;

        UpdateSplat(mousePosition, direction, colour);
        m_PreviousMousePosition = mousePosition;
    }

    m_CurlProgramShader.Bind();
    m_CurlProgramShader.SetUniform("texelSize", Vector2f(1.0f / m_TextureWidth, 1.0f / m_TextureHeight));
    m_CurlProgramShader.SetUniform("velocity", m_VelocityFrameBufferObject.GetReadBuffer().TextureId);
    
    Blit(m_CurlFrameBufferObject);

    m_VorticityProgramShader.Bind();
    m_VorticityProgramShader.SetUniform("texelSize", Vector2f(1.0f / m_TextureWidth, 1.0f / m_TextureHeight));
    m_VorticityProgramShader.SetUniform("velocity", m_VelocityFrameBufferObject.GetReadBuffer().TextureId);
    m_VorticityProgramShader.SetUniform("curlSampler", m_CurlFrameBufferObject.TextureId);
    m_VorticityProgramShader.SetUniform("curl", Settings.Curl);
    m_VorticityProgramShader.SetUniform("dt", deltaTime);

    Blit(m_VelocityFrameBufferObject.GetWriteBuffer());
    m_VelocityFrameBufferObject.Swap();

    m_DivergenceProgramShader.Bind();
    m_DivergenceProgramShader.SetUniform("texelSize", Vector2f(1.0f / m_TextureWidth, 1.0f / m_TextureHeight));
    m_DivergenceProgramShader.SetUniform("velocity", m_VelocityFrameBufferObject.GetReadBuffer().TextureId);

    Blit(m_DivergenceFrameBufferObject);

    m_ClearProgramShader.Bind();

    glActiveTexture(GL_TEXTURE0 + m_PressureFrameBufferObject.GetReadBuffer().TextureId);
    glBindTexture(GL_TEXTURE_2D, m_PressureFrameBufferObject.GetReadBuffer().Texture);
    m_ClearProgramShader.SetUniform("texture", m_PressureFrameBufferObject.GetReadBuffer().TextureId);
    m_ClearProgramShader.SetUniform("value", Settings.PressureDissipation);

    Blit(m_PressureFrameBufferObject.GetWriteBuffer());
    m_PressureFrameBufferObject.Swap();

    m_PressureProgramShader.Bind();
    m_PressureProgramShader.SetUniform("texelSize", Vector2f(1.0f / m_TextureWidth, 1.0f / m_TextureHeight));
    m_PressureProgramShader.SetUniform("divergence", m_DivergenceFrameBufferObject.TextureId);

    m_PressureProgramShader.SetUniform("pressure", m_PressureFrameBufferObject.GetReadBuffer().TextureId);
    glActiveTexture(GL_TEXTURE0 + m_PressureFrameBufferObject.GetReadBuffer().TextureId);
    for (int i = 0; i < Settings.PressureIterations; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, m_PressureFrameBufferObject.GetReadBuffer().Texture);
        Blit(m_PressureFrameBufferObject.GetWriteBuffer());
        m_PressureFrameBufferObject.Swap();
    }

    m_GradientProgramShader.Bind();
    m_GradientProgramShader.SetUniform("texelSize", Vector2f(1.0f / m_TextureWidth, 1.0f / m_TextureHeight));
    m_GradientProgramShader.SetUniform("pressure", m_PressureFrameBufferObject.GetReadBuffer().TextureId);
    m_GradientProgramShader.SetUniform("velocity", m_VelocityFrameBufferObject.GetReadBuffer().TextureId);
    Blit(m_VelocityFrameBufferObject.GetWriteBuffer());
    m_VelocityFrameBufferObject.Swap();*/

    Window& window = Window::Get();
    const int windowWidth = window.GetWidth();
    const int windowHeight = window.GetHeight();
    glViewport(0, 0, windowWidth, windowHeight);

    m_DisplayProgramShader.Bind();
    //m_DisplayProgramShader.SetUniform("texture", m_DensityFrameBufferObject.GetReadBuffer().TextureId);
    Blit(FrameBufferObject::Empty);
    Shader::Unbind();
}

void FluidRenderer::UpdateSplat(const Vector2f& position, const Vector2f& direction, const Vector4f& colour)
{
    Window& window = Window::Get();
    const int windowWidth = window.GetWidth();
    const int windowHeight = window.GetHeight();
    const float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

    m_SplatProgramShader.Bind();
    m_SplatProgramShader.SetUniform("target", m_VelocityFrameBufferObject.GetReadBuffer().TextureId);
    m_SplatProgramShader.SetUniform("aspectRatio", aspectRatio);

    const Vector2f point(position.X / windowWidth, 1.0f - position.Y / windowHeight);
    m_SplatProgramShader.SetUniform("point", point);
    m_SplatProgramShader.SetUniform("colour", { direction.X, -direction.Y, 1.0 });
    m_SplatProgramShader.SetUniform("radius", Settings.SplatRadius);
    
    Blit(m_VelocityFrameBufferObject.GetWriteBuffer());
    m_VelocityFrameBufferObject.Swap();

    m_SplatProgramShader.SetUniform("target", m_DensityFrameBufferObject.GetReadBuffer().TextureId);
    m_SplatProgramShader.SetUniform("colour", colour * 0.3f);
    
    Blit(m_DensityFrameBufferObject.GetWriteBuffer());
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
        const Vector2f direction = { 1000 * (Random::Value() - 0.5f), 1000 * (Random::Value() - 0.5f) };

        UpdateSplat(position, direction, colour);
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

void FluidRenderer::GenerateBlitSurface()
{
    glGenBuffers(1, &m_BlitSurfaceVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_BlitSurfaceVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, s_BlitSurfaceVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_BlitSurfaceIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BlitSurfaceIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * 6, s_BlitSurfaceIndices, GL_STATIC_DRAW);

}

void FluidRenderer::Blit(const FrameBufferObject& frameBufferObject) const
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_BlitSurfaceVertexBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BlitSurfaceIndexBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject.ObjectHandle);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(0);
}

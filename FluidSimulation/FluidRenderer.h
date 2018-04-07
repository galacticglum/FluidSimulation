#pragma once

#include <stack>
#include <GL/glew.h>

#include "Shader.h"
#include "Maths.h"

#include "FrameBufferObject.h"
#include "DoubleFrameBufferObject.h"

struct FluidRendererSettings
{
	int TextureDownsample = 1;
	float DensityDissipation = 0.98f;
	float VelocityDissipation = 0.99f;
	float PressureDissipation = 0.80f;
	int PressureIterations = 25;
	int Curl = 30;
	float SplatRadius = 0.005f;
};

class FluidRenderer
{
public:
	FluidRenderer();
	FluidRendererSettings Settings;

    void Update(float deltaTime);
private:
	std::stack<int> m_SplatStack;

    Shader m_ClearProgramShader;
    Shader m_DisplayProgramShader;
    Shader m_SplatProgramShader;
    Shader m_AdvectionProgramShader;
    Shader m_DivergenceProgramShader;
    Shader m_CurlProgramShader;
    Shader m_VorticityProgramShader;
    Shader m_PressureProgramShader;
    Shader m_GradientProgramShader;

    int m_TextureWidth;
    int m_TextureHeight;

    DoubleFrameBufferObject m_DensityFrameBufferObject;
    DoubleFrameBufferObject m_VelocityFrameBufferObject;
    FrameBufferObject m_DivergenceFrameBufferObject;
    FrameBufferObject m_CurlFrameBufferObject;
    DoubleFrameBufferObject m_PressureFrameBufferObject;

    Vector2f m_PreviousMousePosition;

    void UpdateSplat(const Vector2f& position, const Vector2f& direction, const Vector4f& colour);
    void BatchSplats(int amount);

    void InitializeFrameBuffers();
    static void Blit(const FrameBufferObject& frameBufferObject);
};

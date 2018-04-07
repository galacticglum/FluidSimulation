#pragma once

#include <stack>

struct FluidRendererSettings
{
	int TextureDownsample = 1;
	float DensityDissipation = 0.98;
	float VelocityDissipation = 0.99;
	float PressureDissipation = 0.80;
	int PressureIterations = 25;
	int Curl = 30;
	float SplatRadius = 0.005;
};

class FluidRenderer
{
public:
	FluidRenderer();
	~FluidRenderer();

	FluidRendererSettings Settings;
private:
	std::stack<int> m_SplatStack;
};


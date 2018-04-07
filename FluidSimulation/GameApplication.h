#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <cmath>

class Window;
class GameApplication
{
public:
	inline GameApplication(int width, int height) : 
		GameApplication(width, height, "Window", 60) {}

	inline GameApplication(int width, int height, const std::string& windowTitle) : 
		GameApplication(width, height, windowTitle, 60) {}

	inline GameApplication(int width, int height, const std::string& windowTitle, double frameRate) : 
		m_FrameTime(1.0 / frameRate), m_Running(false), m_Width(width), m_Height(height), m_WindowTitle(windowTitle) {}

	void Start();
	void Stop();

	inline int GetUPS() { return this->m_UpdatesPerSecond; }
	inline int GetFPS() { return this->m_FramesPerSecond; }
	inline Window* GetWindow() { return this->m_Window; }
private:
	std::string m_WindowTitle;
	Window* m_Window;

	bool m_Running;
	double m_FrameTime;

	int m_UpdatesPerSecond;
	int m_FramesPerSecond;

	int m_Width;
	int m_Height;

	void Run();

	void Initialize();
	void Update(float deltaTime);
	void Render();
	void OnGui();
	void Shutdown();
};
#pragma once

#include <thread>

class GameApplication
{
public:
    GameApplication(const int width, const int height) : 
		GameApplication(width, height, "Window", 60) {}

    GameApplication(const int width, const int height, const std::string& windowTitle) : 
		GameApplication(width, height, windowTitle, 60) {}

    GameApplication(int width, int height, const std::string& windowTitle, double frameRate);

	void Start();
	void Stop();

    int GetUPS() const { return m_UpdatesPerSecond; }
    int GetFPS() const { return m_FramesPerSecond; }
private:
	std::string m_WindowTitle;

	bool m_Running;
	double m_FrameTime;

	int m_UpdatesPerSecond{};
	int m_FramesPerSecond{};

	int m_Width;
	int m_Height;

	void Run();

    void Initialize();
	void Update(float deltaTime);
	void Render() const;
	void OnGui() const;
    static void Shutdown();
};
#include "GameApplication.h"
#include "Time.h"
#include "Window.h"
#include <thread>
#include <utility>
#include "Input.h"

/**
 * \brief Initializes the game application.
 * \param width The width of the game window.
 * \param height The height of the game window.
 * \param windowTitle The title of the game window.
 * \param frameRate The target framerate to run at.
 */
GameApplication::GameApplication(const int width, const int height, std::string windowTitle, const double frameRate) :
    m_WindowTitle(std::move(windowTitle)), m_Running(false), m_FrameTime(1.0 / frameRate), m_UpdatesPerSecond(0),
    m_FramesPerSecond(0),
    m_Width(width), m_Height(height)
{
}

void GameApplication::Start()
{
    if (m_Running) return;

	Window& window = Window::Get();
    window.Initialize(m_WindowTitle, m_Width, m_Height);

	Run();
}

void GameApplication::Stop()
{
    if (!m_Running) return;
	m_Running = false;
}

void GameApplication::Run()
{
	m_Running = true;

	double lastFrameTime = Time::GetTime();
	double frameTimer = 0;
	double updateTimer = 0;

	int frameCount = 0;
	int updateCount = 0;

	Initialize();
	while (m_Running)
	{
		bool doRender = false;
	    const double currentFrameTime = Time::GetTime();
	    const double passedFrameTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		updateTimer += passedFrameTime;
		frameTimer += passedFrameTime;

		if (frameTimer >= 1.0)
		{
			m_UpdatesPerSecond = updateCount;
			m_FramesPerSecond = frameCount;

			frameCount = 0;
			updateCount = 0;
			frameTimer = 0;
		}

		while (updateTimer > m_FrameTime)
		{
			if (Window::Get().IsCloseRequested())
			{
				Stop();
			}

            Input::Update();
			Update(static_cast<float>(m_FrameTime));

			doRender = true;
			updateTimer -= m_FrameTime;
			updateCount++;
		}

		if (doRender)
		{
			Render();
			frameCount++;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	Shutdown();
}

void GameApplication::Initialize()
{
    //m_FluidRenderer = std::make_unique<FluidRenderer>();
    glGenBuffers(1, &vboID);
    static GLfloat vertices[] = { -1, -1, 1, -1, 0, 1 };

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GameApplication::Update(const float deltaTime)
{
}

void GameApplication::Render()
{
    Window& window = Window::Get();
    window.MakeContextCurrent();

    Window::Clear();
    //m_FluidRenderer->Update(m_FrameTime);

    m_TestShaderProgram = Shader("Assets/Shaders/test.vert", "Assets/Shaders/test.frag");
    m_TestShaderProgram.Bind();
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);

    window.Update();
}

void GameApplication::Shutdown()
{
}
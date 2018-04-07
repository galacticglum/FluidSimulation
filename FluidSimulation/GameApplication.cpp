#include "GameApplication.h"
#include "Time.h"
#include "Window.h"
#include "imgui/ImGuiSystem.h"
#include <thread>

/**
 * \brief Initializes the game application.
 * \param width The width of the game window.
 * \param height The height of the game window.
 * \param windowTitle The title of the game window.
 * \param frameRate The target framerate to run at.
 */
GameApplication::GameApplication(const int width, const int height, const std::string& windowTitle, const double frameRate) :
    m_WindowTitle(windowTitle), m_Running(false), m_FrameTime(1.0 / frameRate), m_UpdatesPerSecond(0),
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
	// Initialize ImGui
    ImGuiSystem::Init(Window::Get().GetGLFWwindow(), true);
	ImGui::StyleColorsClassic();

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
    m_FluidRenderer = std::make_unique<FluidRenderer>();
}

void GameApplication::Update(const float deltaTime) const
{
    m_FluidRenderer->Update(deltaTime);
}

void GameApplication::Render() const
{
    Window& window = Window::Get();
    window.MakeContextCurrent();
	window.Update();

	ImGuiSystem::NewFrame();
	OnGui();

    Window::Clear();
	ImGui::Render();
}

bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void GameApplication::OnGui() const
{
	{
		static float f = 0.0f;
		ImGui::Text("Hello, world!");                           // Some text (you can use a format string too)
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float as a slider from 0.0f to 1.0f
        if (ImGui::ColorEdit3("clear color", reinterpret_cast<float*>(&clear_color)))
        {
            Window::SetClearColour(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        }
		if (ImGui::Button("Demo Window"))                       // Use buttons to toggle our bools. We could use Checkbox() as well.
			show_demo_window ^= 1;
		if (ImGui::Button("Another Window"))
			show_another_window ^= 1;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		ImGui::End();
	}

	if (show_demo_window)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
		ImGui::ShowDemoWindow(&show_demo_window);
	}
}

void GameApplication::Shutdown()
{
	ImGuiSystem::Shutdown();
}
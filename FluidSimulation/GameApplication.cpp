#include "GameApplication.h"
#include "Window.h"
#include "Time.h"
#include "imgui/ImGuiSystem.h"

void GameApplication::Start()
{
	if (m_Running == true)
	{
		return;
	}

	m_Window = new Window(m_WindowTitle, m_Width, m_Height);
	Run();
}

void GameApplication::Stop()
{
	if (m_Running == false)
	{
		return;
	}

	m_Running = false;
}

void GameApplication::Run()
{
	// Initialize ImGui
	ImGuiSystem::Init(m_Window->GetGLFWwindow(), true);
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
		double currentFrameTime = Time::GetTime();
		double passedFrameTime = currentFrameTime - lastFrameTime;
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
			if (m_Window->IsCloseRequested())
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
}

void GameApplication::Update(float deltaTime)
{
}

void GameApplication::Render()
{
	m_Window->MakeContextCurrent();
	m_Window->Update();

	ImGuiSystem::NewFrame();
	OnGui();

	m_Window->Clear();
	ImGui::Render();
}

bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void GameApplication::OnGui()
{
	{
		static float f = 0.0f;
		ImGui::Text("Hello, world!");                           // Some text (you can use a format string too)
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float as a slider from 0.0f to 1.0f
        if (ImGui::ColorEdit3("clear color", (float*)&clear_color))
        {
            m_Window->SetClearColour(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        }
		if (ImGui::Button("Demo Window"))                       // Use buttons to toggle our bools. We could use Checkbox() as well.
			show_demo_window ^= 1;
		if (ImGui::Button("Another Window"))
			show_another_window ^= 1;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	// 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name the window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		ImGui::End();
	}

	// 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow().
	if (show_demo_window)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
		ImGui::ShowDemoWindow(&show_demo_window);
	}
}

void GameApplication::Shutdown()
{
	ImGuiSystem::Shutdown();
	delete m_Window;
}
#include "Window.h"

void WindowResizeCallback(GLFWwindow* window, int width, int height);

Window::Window(std::string title, int width, int height) :
	m_Title(title), m_Width(width), m_Height(height)
{
	if (!Initialize())
	{
		glfwTerminate();
	}

	//Input::Initialize(this);
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::Initialize()
{
	if (!glfwInit())
	{
		std::cout << "Window::Initialize: Failed to initialize GLFW!\n";
		return false;
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	if (!m_Window)
	{
		std::cout << "Window::Initialize: Failed to create window!\n";
		return false;
	}

	glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);
	MakeContextCurrent();

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Window::Initialize: Failed to initialize GLEW!\n";
		return false;
	}

	std::cout << "OpenGL " << glGetString(GL_VERSION) << "\n";
	return true;
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Window::SetTitle(std::string title)
{
	m_Title = title;
	glfwSetWindowTitle(m_Window, m_Title.c_str());
}

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
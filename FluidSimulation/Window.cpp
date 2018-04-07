#include "Window.h"

void WindowResizeCallback(GLFWwindow* window, int width, int height);

Window::Window(std::string title, int width, int height) :
	m_Title(title), m_Width(width), m_Height(height)
{
	if (!this->Initialize())
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

	this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height, this->m_Title.c_str(), nullptr, nullptr);
	if (!this->m_Window)
	{
		std::cout << "Window::Initialize: Failed to create window!\n";
		return false;
	}

	glfwSetWindowSizeCallback(this->m_Window, WindowResizeCallback);

	this->MakeContextCurrent();

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
	glfwSwapBuffers(this->m_Window);
}

void Window::SetTitle(std::string title)
{
	this->m_Title = title;
	glfwSetWindowTitle(this->m_Window, this->m_Title.c_str());
}

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
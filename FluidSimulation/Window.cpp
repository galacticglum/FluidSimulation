#include "Window.h"

#include <iostream>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void WindowResizeCallback(GLFWwindow* window, int width, int height);

Window::~Window()
{
	glfwTerminate();
}

bool Window::InitializeGlfwBackend()
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

Window& Window::Get()
{
    static Window window;
    return window;
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Initialize(const std::string& title, const int width, const int height)
{
    if (m_Window != nullptr) return;

    m_Title = title;
    m_Width = width;
    m_Height = height;

    if (!InitializeGlfwBackend())
    {
        glfwTerminate();
    }
}

void Window::Update() const
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Window::MakeContextCurrent() const
{
    glfwMakeContextCurrent(m_Window);
}

bool Window::IsCloseRequested() const
{
    return glfwWindowShouldClose(m_Window) == 1;
}

int Window::GetWidth() const
{
    return m_Width;
}

int Window::GetHeight() const
{
    return m_Height;
}

GLFWwindow* Window::GetGLFWwindow() const
{
    return m_Window;
}

void Window::SetClearColour(const float red, const float green, const float blue, const float alpha)
{
    glClearColor(red, green, blue, alpha);
}

void Window::SetTitle(const std::string& title)
{
	m_Title = title;
	glfwSetWindowTitle(m_Window, m_Title.c_str());
}

void WindowResizeCallback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}
#include "InputManager.h"
#include "Window.h"

void CursorPositionCallback(GLFWwindow* window, const double xpos, const double ypos)
{
    auto* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    inputManager->m_MouseX = static_cast<float>(xpos);
    inputManager->m_MouseY = static_cast<float>(ypos);
}

InputManager::InputManager() : m_MouseX(0), m_MouseY(0), m_Window(Window::Get().GetGLFWwindow())
{
    for (int i = 0; i < MAX_KEYS; i++)
    {
        this->m_Keys[i] = false;
        this->m_DownKeys[i] = false;
        this->m_UpKeys[i] = false;
    }

    for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
    {
        this->m_MouseButtons[i] = false;
        this->m_DownMouseButtons[i] = false;
        this->m_UpMouseButtons[i] = false;
    }

    glfwSetWindowUserPointer(this->m_Window, this);
    glfwSetCursorPosCallback(this->m_Window, CursorPositionCallback);
}

void InputManager::Update()
{
    for (int i = 0; i < MAX_KEYS; i++)
    {
        this->m_UpKeys[i] = false;
        this->m_DownKeys[i] = false;

        if (!this->GetKey(static_cast<Key>(i)) && this->m_Keys[i])
        {
            this->m_UpKeys[i] = true;
        }

        if (this->GetKey(static_cast<Key>(i)) && !this->m_Keys[i])
        {
            this->m_DownKeys[i] = true;
        }

        this->m_Keys[i] = false;
        if (this->GetKey(static_cast<Key>(i)))
        {
            this->m_Keys[i] = true;
        }
    }

    for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
    {
        this->m_UpMouseButtons[i] = false;
        this->m_DownMouseButtons[i] = false;

        if (!this->GetMouseButton(static_cast<MouseButton>(i)) && this->m_MouseButtons[i])
        {
            this->m_UpMouseButtons[i] = true;
        }

        if (this->GetMouseButton(static_cast<MouseButton>(i)) && !this->m_MouseButtons[i])
        {
            this->m_DownMouseButtons[i] = true;
        }

        this->m_MouseButtons[i] = false;
        if (this->GetMouseButton(static_cast<MouseButton>(i)))
        {
            this->m_MouseButtons[i] = true;
        }
    }
}
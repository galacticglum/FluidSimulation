#pragma once

#include "Maths.h"
#include "GLFW/glfw3.h"
#include "Input.h"

#define MAX_KEYS 512
#define MAX_MOUSE_BUTTONS 256

class InputManager
{
public:
    explicit InputManager();
    void Update();

    bool GetKey(Key key) const { return glfwGetKey(this->m_Window, static_cast<int>(key)) == GLFW_PRESS; }
    bool GetKeyDown(Key key) { return this->m_DownKeys[static_cast<int>(key)]; }
    bool GetKeyUp(Key key) { return this->m_UpKeys[static_cast<int>(key)]; }

    bool GetMouseButton(MouseButton mouseButton) const { return glfwGetMouseButton(this->m_Window, static_cast<int>(mouseButton)) == GLFW_PRESS; }
    bool GetMouseButtonDown(MouseButton mouseButton) { return this->m_DownMouseButtons[static_cast<int>(mouseButton)]; }
    bool GetMouseButtonUp(MouseButton mouseButton) { return this->m_UpMouseButtons[static_cast<int>(mouseButton)]; }

    Vector2f GetMousePosition() const { return {m_MouseX, m_MouseY}; }
    void SetMousePosition(const float x, const float y) const { this->SetMousePosition(Vector2f(x, y)); }
    void SetMousePosition(const Vector2f& position) const { glfwSetCursorPos(this->m_Window, position.X, position.Y); }

    bool GetCursorVisibility() const { return (glfwGetInputMode(this->m_Window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL); }
    void ShowCursor(const bool visibility) const { glfwSetInputMode(this->m_Window, GLFW_CURSOR, visibility ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN); }
private:
    bool m_Keys[MAX_KEYS]{};
    bool m_DownKeys[MAX_KEYS]{};
    bool m_UpKeys[MAX_KEYS]{};

    bool m_MouseButtons[MAX_MOUSE_BUTTONS]{};
    bool m_DownMouseButtons[MAX_MOUSE_BUTTONS]{};
    bool m_UpMouseButtons[MAX_MOUSE_BUTTONS]{};

    float m_MouseX;
    float m_MouseY;

    GLFWwindow* m_Window{};

    friend static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
};

#include "Input.h"
#include "InputManager.h"

std::unique_ptr<InputManager> Input::s_InputManager;
void Input::Initialize()
{
    s_InputManager = std::make_unique<InputManager>();
}

void Input::Update()
{
    return s_InputManager->Update();
}

bool Input::GetKey(Key key)
{
    return s_InputManager->GetKey(key);
}

bool Input::GetKeyDown(Key key)
{
    return s_InputManager->GetKeyDown(key);
}

bool Input::GetKeyUp(Key key)
{
    return s_InputManager->GetKeyUp(key);
}

bool Input::GetMouseButton(MouseButton mouseButton)
{
    return s_InputManager->GetMouseButton(mouseButton);
}

bool Input::GetMouseButtonDown(MouseButton mouseButton)
{
    return s_InputManager->GetMouseButtonDown(mouseButton);
}

bool Input::GetMouseButtonUp(MouseButton mouseButton)
{
    return s_InputManager->GetMouseButtonUp(mouseButton);
}

Vector2f Input::GetMousePosition()
{
    return s_InputManager->GetMousePosition();
}

void Input::SetMousePosition(const Vector2f& position)
{
    s_InputManager->SetMousePosition(position);
}

bool Input::GetCursorVisibility()
{
    return s_InputManager->GetCursorVisibility();
}

void Input::ShowCursor(bool visibility)
{
    s_InputManager->ShowCursor(visibility);
}
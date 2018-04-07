#pragma once

#include <string>

struct GLFWwindow;
class Window
{
public:
    Window(const Window&& other) = delete;
    Window& operator=(Window&& other) = delete;

    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;

    /**
     * \brief Get the static window instance.
     * \return The window instance.
     */
    static Window& Get();
    static void Clear();

    void Initialize(const std::string& title = "", int width = 0, int height = 0);
    void Update() const;

    void MakeContextCurrent() const;

    bool IsCloseRequested() const;
    int GetWidth() const;
    int GetHeight() const;
    GLFWwindow* GetGLFWwindow() const;

	void SetTitle(const std::string& title);
    static void SetClearColour(float red, float green, float blue, float alpha);
private:
    Window() = default;
    ~Window();

	GLFWwindow* m_Window{};
	std::string m_Title;

	int m_Width{};
	int m_Height{};

	bool InitializeGlfwBackend();
};
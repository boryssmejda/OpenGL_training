#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>

int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glewInit();
    /* Create a windowed mode window and its OpenGL context */
    auto windowDeleter = [](GLFWwindow* w) {
        std::cout << "Closing the window!\n";
        glfwTerminate();
    };
    std::unique_ptr<GLFWwindow, decltype(windowDeleter)> glfwWindow(
        glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr), windowDeleter);

    if (!glfwWindow)
    {
        std::cout << "Couldn't create a Window\n";
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(glfwWindow.get());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glfwWindow.get()))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(glfwWindow.get());

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void windowDeleter(GLFWwindow* t_w);
void frameBufferSizeCallback(GLFWwindow* t_window, int t_width, int t_height);
void processInput(std::unique_ptr < GLFWwindow, decltype(&windowDeleter)>& t_glfwWindow);

int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		std::cout << "We are on MacOS\n";
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif


    /* Create a windowed mode window and its OpenGL context */
    std::unique_ptr<GLFWwindow, decltype(&windowDeleter)> glfwWindow(
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", nullptr, nullptr), windowDeleter);

    if (!glfwWindow)
    {
        std::cout << "Couldn't create a Window\n";
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(glfwWindow.get());
    glfwSetFramebufferSizeCallback(glfwWindow.get(), frameBufferSizeCallback);

    if (glewInit() != GLEW_OK)
        std::cout << "Error creating GLEW\n";

    std::cout << glGetString(GL_VERSION) << '\n';

    float positions[6] = {
        -0.5f, -0.5f,
        0.5f,  -0.5f,
        0.0f,   0.5f
    };

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glfwWindow.get()))
    {
        processInput(glfwWindow);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(glfwWindow.get());

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}

void frameBufferSizeCallback(GLFWwindow* t_window, int t_width, int t_height)
{
    std::cout << "Resizing window!\n"
        "New Width: " << t_width << '\n' <<
        "New Height: " << t_height << '\n' <<
        "--------------------------------\n";
    glViewport(0, 0, t_width, t_height);
}


void processInput(std::unique_ptr <GLFWwindow, decltype(&windowDeleter)>& t_glfwWindow)
{
    if (glfwGetKey(t_glfwWindow.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        std::cout << "Escape key was pressed!\n";
        glfwSetWindowShouldClose(t_glfwWindow.get(), true);
    }
}


void windowDeleter(GLFWwindow* t_w)
{
    std::cout << "Closing the window!\n";
    glfwTerminate();
}
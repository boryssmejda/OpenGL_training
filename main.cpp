#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include "debugHelper.hpp"
#include "Shader.hpp"

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

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << nrAttributes << '\n';


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    glCheckError();
    Shader shader("../shaders/vertexShader.vs", "../shaders/fragmentShader.fs");
    glCheckError();
    // set up vertex data and configure vertex attributes
    // --------------------------------------------------

    float triangle[] = {
        -0.8f, 0.8f, 1.0f, 0.0f, 0.0f,
        -0.6f, 0.8f, 0.0f, 1.0f, 0.0f,
        -0.7f, 0.6f, 0.0f, 0.0f, 1.0f
    };

    unsigned int triangleVertexArray, trVBO;
    
    glCreateVertexArrays(1, &triangleVertexArray);
    glGenBuffers(1, &trVBO);
    glCheckError();

    glBindVertexArray(triangleVertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, trVBO);
    glCheckError();

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glCheckError();

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));
    glCheckError();
    // ---------------------------------------------------------
    float vertices[] = {
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,  // first triangle
        2, 3, 0   // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glCheckError();

    glBindVertexArray(VAO);
    glCheckError();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glCheckError();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glCheckError();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
    glCheckError();

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glCheckError();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glCheckError();

    glEnableVertexAttribArray(0);
    glCheckError();

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glCheckError();
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float offsetX = 0.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glfwWindow.get()))
    {
        processInput(glfwWindow);
        int state = glfwGetKey(glfwWindow.get(), GLFW_KEY_RIGHT);
        if (state == GLFW_PRESS)
        {
            offsetX += 0.01f;
        }

        state = glfwGetKey(glfwWindow.get(), GLFW_KEY_LEFT);
        if (state == GLFW_PRESS)
        {
            offsetX -= 0.01f;
        }

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setFloat("currentX", offsetX);
        glCheckError();

        // now render the triangle
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glCheckError();

        glBindVertexArray(triangleVertexArray);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glCheckError();

        /* Swap front and back buffers */
        glfwSwapBuffers(glfwWindow.get());

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    

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
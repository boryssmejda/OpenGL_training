#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <string>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void windowDeleter(GLFWwindow* t_w);
void frameBufferSizeCallback(GLFWwindow* t_window, int t_width, int t_height);
void processInput(std::unique_ptr < GLFWwindow, decltype(&windowDeleter)>& t_glfwWindow);

static int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (GL_FALSE == success)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        std::string infolog(length, '\0');
        std::cout << "Compilation failed!\n";
        glGetShaderInfoLog(id, length, &length, &infolog[0]);
        std::cout << infolog << '\n';
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader )
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    //glDeleteShader(vs);
    //glDeleteShader(fs);

    return program;
}

int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

	  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
      //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

    // set up vertex data and configure vertex attributes
    // --------------------------------------------------

    float vertices[] = {
        -0.5f, 0.0f,
         0.5f, 0.0f,
         0.0f, 0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::string vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec4 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = aPos;\n"
        "}\n";

    std::string fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
        "}\n";

    unsigned int shader = CreateShader(vertexShaderSource, fragmentShaderSource);
    glUseProgram(shader);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glfwWindow.get()))
    {
        processInput(glfwWindow);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(glfwWindow.get());

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);
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
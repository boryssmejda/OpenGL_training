#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <stdexcept>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void windowDeleter(GLFWwindow* t_w);
void frameBufferSizeCallback(GLFWwindow* t_window, int t_width, int t_height);
void processInput(std::unique_ptr < GLFWwindow, decltype(&windowDeleter)>& t_glfwWindow);

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << std::hex << error << ")" << std::dec << std::endl;
        std::cout << "Error observed in " << function << " " << file << " : " << line << '\n';
        return false;
    }
    return true;
}

using VertexShaderSource = std::string;
using FragmentShaderSource = std::string;

static std::pair<VertexShaderSource, FragmentShaderSource> ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    if (!stream)
    {
        throw std::runtime_error("Could not open the file!");
    }
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[static_cast<int>(type)] << line << '\n';
        }
            
    }

    return {
            ss[static_cast<int>(ShaderType::VERTEX)].str(),
            ss[static_cast<int>(ShaderType::FRAGMENT)].str()
    };
}

static int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int success;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

    if (GL_FALSE == success)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        std::string infolog(length, '\0');
        std::cout << "Compilation failed!\n";
        GLCall(glGetShaderInfoLog(id, length, &length, &infolog[0]));
        std::cout << infolog << '\n';
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader )
{
    unsigned int program;
    GLCall(program = glCreateProgram());
    unsigned int vs, fs;
    GLCall(vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
    GLCall(fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

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
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error creating GLEW\n";

    std::cout << glGetString(GL_VERSION) << '\n';

    // set up vertex data and configure vertex attributes
    // --------------------------------------------------

    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f, 0.5f,
         -0.5f, 0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned VAO;
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));

    unsigned int buffer;
    GLCall(glGenBuffers(1, &buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    std::string filepath = "../resources/shaders/shaders.shader";
    auto [vertexShaderSource, fragmentShaderSource] = ParseShader(filepath);

    unsigned int shader = CreateShader(vertexShaderSource, fragmentShaderSource);
    GLCall(glUseProgram(shader));

    int location;
    GLCall(location = glGetUniformLocation(shader, "u_Color"));
    GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));

    // uncomment this call to draw in wireframe polygons.
    //GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
   
    float r = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glfwWindow.get()))
    {
        processInput(glfwWindow);

        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;

        /* Render here */
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        

        /* Swap front and back buffers */
        glfwSwapBuffers(glfwWindow.get());

        /* Poll for and process events */
        glfwPollEvents();
    }

    GLCall(glDeleteProgram(shader));
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
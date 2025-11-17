/*
* Title: Linear Transformations: Module 4 - Transformations
* Description: This program will render the translated, rotated, scaled, and skewed versions of original square
* Author: Prince Niyonkuru
* Date: 09/30/2024
* Version number: g++ 13.2.0, gcc 11.4.0
* Requirements: This program requires GLEW, GLFW, and GLM librarieS
* Version requirement: This program requires GLFW 3.3 or above
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                //set mode to vertex
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                //set mode to fragment
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    //if a shader doesn't compile correctly
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile"<< 
            (type == GL_VERTEX_SHADER ? "vertex": "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
     

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(900, 900, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    if (glewInit() == GLEW_OK)
        std::cout << "No Error with glewInit!" << std::endl;

    float positions[] = {
        -0.1f, -0.1f, //0 bottome left
         0.1f,  -0.1f,//1 bottom right
         0.1f, 0.1f,  //2 top right
         -0.1f, 0.1f, //3 top left
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER,8 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int indxBufferObject;
    glGenBuffers(1, &indxBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indxBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    ShaderProgramSource source = ParseShader("shaders/basic.shader");
    /*std::cout << "VERTEX" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << source.FragmentSource << std::endl;*/

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    // Store the location of the transform uniform
    unsigned int transformLoc = glGetUniformLocation(shader, "transform");
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.4,0.4,0.1,1.0);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glBindVertexArray(VAO);
        glm::mat4 transform = glm::mat4(1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glUniform4f(glGetUniformLocation(shader, "vertexColor"), 1.0f, 0.0f, 0.0f, 1.0f);  // Red
        glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, nullptr);

        /**/
       // Translated with a value of 0.3 because if i use 1.5f, the result is outside of the screen since openGL window goes from -1 to 1
        glm::mat4 transform_translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, 0.0f, 0.0f));  // Translate
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_translate));
        glUniform4f(glGetUniformLocation(shader, "vertexColor"), 1.0f, 0.5f, 0.5f, 1.0f);  // Pink
        glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, nullptr);

        glm::mat4 transform_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f),  glm::vec3(0.0f, 0.0f, 1.0f));  // Translate
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_rotate));
        glUniform4f(glGetUniformLocation(shader, "vertexColor"), 0.0f, 1.0f, 0.0f, 1.0f);  // Green
        glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, nullptr);

        glm::mat4 transform_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.0f));  // Translate
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_scale));
        glUniform4f(glGetUniformLocation(shader, "vertexColor"), 0.0f, 0.0f, 1.0f, 1.0f);  // Blue
        glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, nullptr);
        

        glm::mat4 transform_skew = glm::mat4(1.0f);
        transform_skew[1][0] = 0.5f;
        transform_skew[0][1] = 0.2f;
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_skew));
        glUniform4f(glGetUniformLocation(shader, "vertexColor"), 0.0f, 1.0f, 1.0f, 1.0f);  // Light Blue
        glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
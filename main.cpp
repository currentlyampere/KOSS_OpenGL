#include <glad/glad.h>
//function loader
#include <GLFW/glfw3.h>
//talks to OS
#include <iostream>

int main() {
    //INTIALIZING
    if (!glfwInit()) 
        return -1;
    //WINDOW POINTER
    GLFWwindow* window = glfwCreateWindow(800, 600, "KOSS OpenGL Window", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }
    //CONTEXT
    glfwMakeContextCurrent(window);
    //LOADING OPENGL FUNCTIONS
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
//Defining Vertices of Triangle
    float vertices[] = {
     0.0f,  0.5f, 0.0f,   // top
    -0.5f, -0.5f, 0.0f,   // left
     0.5f, -0.5f, 0.0f    // right
    };
//(VBO)Sending this data to a memory block in GPU(buffer)
    unsigned int VBO;                       //creating ID for Buffer
    glGenBuffers(1, &VBO);                  // creating buffer and storing its ID
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     // Sets VBO as current buffer. GL_ARRAY_BUFFER=> This buffer will store vertex attributes
    //Filling the buffer with data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //                                                          its gonna be const. data

    //RENDER LOOP
    while (!glfwWindowShouldClose(window)) 
    {      
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);          
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
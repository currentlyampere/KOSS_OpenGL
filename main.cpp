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
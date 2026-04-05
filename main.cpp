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
/*
*/
//(VBO)Sending this data to a memory block in GPU(buffer)
    unsigned int VBO;                       //creating ID for Buffer
    glGenBuffers(1, &VBO);                  // creating buffer and storing its ID
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     // Sets VBO as current buffer. GL_ARRAY_BUFFER=> This buffer will store vertex attributes
    //Filling the buffer with data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //                                                          its gonna be const. data
//(VAO) Telling GPU how to read that data via memory block containing instructions
    unsigned int VAO;                       //creating ID containing that memory block
    glGenVertexArrays(1, &VAO);             // creating memory block and storing its ID
    glBindVertexArray(VAO);                 //selecting this vertex array

    glBindBuffer(GL_ARRAY_BUFFER, VBO);      //telling vertex array to use this vertex buffer

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // real instructions to how to read attributes
    glEnableVertexAttribArray(0);               //turning on attribute on location 
//Writing Shaders as strings..
    const char* vertexShaderSource =
        "#version 330 core\n"                   //version specifcation
        "layout (location = 0) in vec3 aPos;\n"
        //Take input from attribute location 0, which is 3 floats (vec3), and call it aPos
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}\0";
     const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
                           // R   G    B    Alpha
        "}\0";
//Compiling Shaders
    unsigned int vertexShader;                                    //creating ID for shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);              //assign ID to shader
    glShaderSource(vertexShader,   1          , &vertexShaderSource, NULL);   //providing source code to the shader
    //                 id      |only 1 string*| address of string* | lenght of string;since we have null terminated string we dont need it
    //*we can pass more than 1 string and hence we are passing pointer to string(array of string)
    glCompileShader(vertexShader);                                //Compiling the source code

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

//Linking shaders into program

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); 

 // deleting shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

//RENDER LOOP    
    while (!glfwWindowShouldClose(window)) 
    {      
        //clear screen
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);      
       
         //draw traingle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);                 //use this data
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
#include <glad/glad.h>
//function loader
#include <GLFW/glfw3.h>
//talks to OS
#include <iostream>

int main() {

    if (!glfwInit()) 
        return -1;
    /*
    glfwInit intialises the GLFW library.
    -> returns 1, if succeed
    -> returns 0, if fails & call glfwTerminate();
    */
    GLFWwindow* window = glfwCreateWindow(800, 600, "KOSS OpenGL Window", NULL, NULL);
    /*   *1                              [size(wxh)]  [Name of window]    *2     [sharing resources to other window or not] 
    *1: glfwCreateWindow creates data type called GLFWwindow which contains all info regarding the window and returns the pointer to that datatype.
        -> if it fails to make window(gpu crashes or something) => it returns NULL.
    
    *2: parameter regarding fullscreen or windowed and in which monitor. NULL means a windowed window.
        ->if we pass glfwGetPrimaryMonitor() as a paremeter then it opens a full screen window in our primary monitor.
        -> there are other paremeters to control seconadary monitors too.
    
    */
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }
   
    glfwMakeContextCurrent(window);
    // -> telling OpenGL we are working on context named window
    //      -> context is like canvas for OpenGL
    //      -> we can switch contexts to work on mutiple window      

    //LOADING OPENGL FUCNTIONS
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
/*
    -> glfwGetProcAddress takes name of OpenGL function, finds it in our OS and then returns the address of it.
    -> gladLoadGLLoader loops over glfwGetProcAddress to find all OpenGL functions and assign them so we can use OpenGL functions
    -> GLADloadproc is just a type cast to make glfw return compatible
    -> and obv if gladLoadGLLoader fails it returns null;
*/
    
    while (!glfwWindowShouldClose(window)) 
    {      // run this loop until user closes the window
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f); //"sets" background color
        //            R    G      B     Alpha
        glClear(GL_COLOR_BUFFER_BIT);          //clears the screen with that color
/*
        - there are two buffers: Front buffer=> i.e. visible
                                 Back Buffer => where all this changes happen
        on glfwSwapBuffers(window), back buffer becomes visible(front) and front buffer becomes next frame to be drawn
        
 */
        glfwSwapBuffers(window);
        glfwPollEvents();
        //checks if user has given any input (mouse/keyboard/window resize and close)
    }
    {/* NO LOOp
       WHY WE NEED RENDERING LOOP?
       -> window only exist when program is running. program over, window over!
       -> without glfwPollEvents(); => close button won’t work =. window freezes =>OS kills it!
       
       so above program can be written as */
    // glClearColor(...);
    // glClear(...);
       glfwSwapBuffers(window);
        while (!glfwWindowShouldClose(window)) 
        {
            glfwPollEvents();   // just keep window alive
        }
    }
    glfwTerminate();
    return 0;
}
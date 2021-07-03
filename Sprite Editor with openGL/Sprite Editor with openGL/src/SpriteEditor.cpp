/* Be sure to include GLAD before GLFW. The include file for GLAD includes the required OpenGL headers behind the scenes
 * (like GL/gl.h) so be sure to include GLAD before other header files that require OpenGL (like GLFW).
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// a function template for resizing the viewport when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    // ==================== GLFW initialization =================== //
    glfwInit(); // initialize GLFW with glfwInit
    /* configure GLFW using glfwWindowHint. The first argument of glfwWindowHint tells us what option we want to configure, 
     * where we can select the option from a large enum of possible options prefixed with GLFW_. The second argument is an 
     * integer that sets the value of our option. A list of all the possible options and its corresponding values can be found at GLFW's window handling documentation.
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // tells GLFW the openGL version we are using, which is 3.3
    /* Telling GLFW we want to use the core-profile means we'll get access to a smaller subset of OpenGL features 
     * without backwards-compatible features we no longer need. 
     * Note that on Mac OS X you need to add glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
     * to your initialization code for it to work.
     */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // ===================== Window creation ==================== //
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // tell GLFW to make the context of our window the main context on the current thread.
    glfwMakeContextCurrent(window);
    // tell GLFW we want to call this function on every window resize by registering it:
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ===================== initialize GLAD ===================== //
    /* GLAD manages function pointers for OpenGL, helps us to query standards/specifications from graphics card supports
     * pass GLAD the function to load the address of the OpenGL function pointers which is OS-specific. 
     * GLFW gives us glfwGetProcAddress that defines the correct function based on which OS we're compiling for.
     */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ==================== Set Viewport ======================== //
    /* The first two parameters of glViewport set the location of the lower left corner of the window. 
     * The third and fourth parameter set the width and height of the rendering window in pixels, 
     * which we set equal to GLFW's window size.
     */
    // initial viewport
    //glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    
    // =================== Render Loop ========================== //
    while (!glfwWindowShouldClose(window)) //  checks at the start of each loop iteration if GLFW has been instructed to close.
    {
        processInput(window);

        // ====================== Render ========================= //
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // state-setting
        // Available bits: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT); // state-using


        glfwSwapBuffers(window); // swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window)
        glfwPollEvents(); // checks if any events are triggered (like keyboard or mouse events), 
        //updates the window state, and calls the corresponding functions (which we can register via callback methods).
    }

    // ======================== QUIT ============================ //
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // if it's not pressed, glfwGetKey returns GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
}

// make sure the viewport matches the new window dimensions; note that width and 
// height will be significantly larger than specified on retina displays.
void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
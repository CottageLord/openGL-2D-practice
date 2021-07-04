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
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    
    // ===================== create shaders ========================= //
        // create the shader with code string, v330 means OpenGL 3.3
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    // bind shader with id
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // dynamically compile the shader code
    // The second argument specifies how many strings we're passing as source code
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check if the compilation succeed
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // create the fragment shader
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
    // bind, initialize and compile the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check if the compilation succeed
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // ======================= Shading Program =================== //
    // link both shader objects into a shader program that we can use for rendering
    // create an empty program object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // attach the created shaders to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // link them into a complete program
    glLinkProgram(shaderProgram);

    // check if the linking succeed
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // clean up the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // =================== define VAO =========================== //
    // create a basic triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // initialze VBO with id
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    // bind the VBO with corresponding, pre-defined openGL buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // copy the triangle data into the GL_ARRAY_BUFFER -> occupied by the VBO
    /*
        *GL_STREAM_DRAW:  the data is set only once and used by the GPU at most a few times.
        GL_STATIC_DRAW:  the data is set only once and used many times.
        GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    // instruct OpenGL how to interpret the vertex data
    glVertexAttribPointer(
        0, // consistent with the layout (location = 0) in the vertex shader, represents the location of the vertex attribute 
        3, // size of the vertext attribute, 3 for vec3
        GL_FLOAT, // the type of the data which is GL_FLOAT
        GL_FALSE, // if we want the data to be normalized. Useful whrn integer data is inputed (will be normalized to -1, 1 or 0)
        3 * sizeof(float), // known as the stride, tells us the space between consecutive vertex attributes. 0 lets OpenGL decide
        (void*)0 // the offset of where the position data begins in the buffer
    );
    // 0 is the attribute position
    glEnableVertexAttribArray(0);

    // ===================== Use EBO to save space =================//
    float rectangle[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    // similar to previous steps
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, // the mode we want to draw in, similar to glDrawArrays
        6,                       // the count or number of elements we'd like to draw (6 indices)
        GL_UNSIGNED_INT,         // type of the indices, which is of type GL_UNSIGNED_INT.
        0);                      // an offset in the EBO (or pass in an index array, 
                    // but that is when you're not using element buffer objects), but we're just going to leave this at 0.
    // 0 is the attribute position
    glEnableVertexAttribArray(0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    // =================== Render Loop ========================== //
    while (!glfwWindowShouldClose(window)) //  checks at the start of each loop iteration if GLFW has been instructed to close.
    {
        processInput(window);

        // ====================== Render ========================= //
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // state-setting
        // Available bits: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT); // state-using

        // active the program
        glUseProgram(shaderProgram);
        // bind the triangle object as the drawing target
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, // type of primitives
            0,  // starting index
            3); // vertices to draw

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window); // swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window)
        glfwPollEvents(); // checks if any events are triggered (like keyboard or mouse events), 
        //updates the window state, and calls the corresponding functions (which we can register via callback methods).
    }

    // ======================== QUIT ============================ //
    glfwTerminate();
    return 0;
}


// ================================== HELPER FUNCTIONS =================================== //

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
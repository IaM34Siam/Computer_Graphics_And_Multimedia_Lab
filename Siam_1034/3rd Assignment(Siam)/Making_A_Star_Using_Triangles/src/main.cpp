#include "glad.h"
#include "glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    //Md.SIam Hosen
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "0432410005101034", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // we skipped compile log checks this time for readability (if you do encounter issues, add the compile-checks! see previous code samples)
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color Blue
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER); // the second fragment shader that outputs the color Green
    unsigned int fragmentShader3 = glCreateShader(GL_FRAGMENT_SHADER);  
    unsigned int fragmentShader4 = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShader5 = glCreateShader(GL_FRAGMENT_SHADER); 
    unsigned int fragmentShader6 = glCreateShader(GL_FRAGMENT_SHADER); 
    unsigned int fragmentShader7 = glCreateShader(GL_FRAGMENT_SHADER); 
    unsigned int fragmentShader8 = glCreateShader(GL_FRAGMENT_SHADER); 

    unsigned int shaderProgram1 = glCreateProgram();
    unsigned int shaderProgram2 = glCreateProgram(); // the second shader program
    unsigned int shaderProgram3 = glCreateProgram();
    unsigned int shaderProgram4 = glCreateProgram();
    unsigned int shaderProgram5 = glCreateProgram(); 
        unsigned int shaderProgram6 = glCreateProgram(); 
            unsigned int shaderProgram7 = glCreateProgram(); 
                unsigned int shaderProgram8 = glCreateProgram(); 
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader1);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader2);
    glShaderSource(fragmentShader3, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader3);
    glShaderSource(fragmentShader4, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader4);
    glShaderSource(fragmentShader5, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader5);
        glShaderSource(fragmentShader6, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader6);
        glShaderSource(fragmentShader7, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader7);
        glShaderSource(fragmentShader8, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader8);
    // link the first program object
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
    // then link the second program object using a different fragment shader (but same vertex shader)
    // this is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

       glAttachShader(shaderProgram3, vertexShader);
    glAttachShader(shaderProgram3, fragmentShader3);
    glLinkProgram(shaderProgram3);

        glAttachShader(shaderProgram4, vertexShader);
    glAttachShader(shaderProgram4, fragmentShader4);
    glLinkProgram(shaderProgram4);

        glAttachShader(shaderProgram5, vertexShader);
    glAttachShader(shaderProgram5, fragmentShader5);
    glLinkProgram(shaderProgram5);

        glAttachShader(shaderProgram6, vertexShader);
    glAttachShader(shaderProgram6, fragmentShader6);
    glLinkProgram(shaderProgram6);

        glAttachShader(shaderProgram7, vertexShader);
    glAttachShader(shaderProgram7, fragmentShader7);
    glLinkProgram(shaderProgram7);

        glAttachShader(shaderProgram8, vertexShader);
    glAttachShader(shaderProgram8, fragmentShader8);
    glLinkProgram(shaderProgram8);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    /*float vertices[] = {
       
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         -0.5f,  0.5f, 0.0f ,
          0.5f,  0.5f, 0.0f,// top 
          0.5f, -0.5f, 0.0f, // right 
         -0.5f,  0.5f, 0.0f
          
    }; */
    float firstTriangle[] = {
        0.3f, 0.3f, 0.0f,  // left 
        -0.3f, 0.3f, 0.0f,  // right
        0.0f, 0.8f, 0.0f  // top 
    };
    float secondTriangle[] = {
        0.3f, 0.3f, 0.0f,  // left 
        0.9f, 0.3f, 0.0f,  // right
        0.5f, -0.2f, 0.0f  // top 
    };
    float thirdTriangle[] = {
        -0.3f, 0.3f, 0.0f,  // left
        -0.9f, 0.3f, 0.0f,  // right
        -0.5f, -0.2f, 0.0f   // top 
    };
    float fourthTriangle[] = {
        -0.5f, -0.2f, 0.0f,  // left
        -0.6f, -0.75f, 0.0f,  // right
        -0.0f, -0.45f, 0.0f   // top 
    };
     float fifthTriangle[] = {
        0.5f, -0.2f, 0.0f,  // left
        0.6f, -0.75f, 0.0f,  // right
        -0.0f, -0.45f, 0.0f   // top 
    };
     float sixthTriangle[] = {
        -0.3f, 0.3f, 0.0f,  // left
        0.3f, 0.3f, 0.0f,  // right
        -0.5f, -0.2f, 0.0f   // top 
    };

 float seventhTriangle[] = {
        0.3f, 0.3f, 0.0f,  // left
        -0.5f, -0.2f, 0.0f,  // right
        0.5f, -0.2f, 0.0f   // top 
    };

 float eighthTriangle[] = {
        -0.5f, -0.2f, 0.0f,  // left
        0.5f, -0.2f, 0.0f,  // right
        -0.0f, -0.45f, 0.0f   // top 
    };


    unsigned int VBOs[8], VAOs[8];
    glGenVertexArrays(8, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(8, VBOs);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)
  glBindVertexArray(VAOs[2]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(thirdTriangle), thirdTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);

      glBindVertexArray(VAOs[3]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(fourthTriangle), fourthTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);


  glBindVertexArray(VAOs[4]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(fifthTriangle), fifthTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[5]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(sixthTriangle), sixthTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[6]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[6]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(seventhTriangle), seventhTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[7]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[7]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(eighthTriangle), eighthTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);



    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // now when we draw the triangle we first use the vertex and Blue fragment shader from the first program
        glUseProgram(shaderProgram1);
        // draw the first triangle using the data from our first VAO
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output an Blue triangle
        // then we draw the second triangle using the data from the second VAO
        // when we draw the second triangle we want to use a different shader program so we switch to the shader program with our Green fragment shader.
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output a Green triangle

        glUseProgram(shaderProgram3);
        glBindVertexArray(VAOs[2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        
        glUseProgram(shaderProgram4);
        glBindVertexArray(VAOs[3]);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glUseProgram(shaderProgram5);
        glBindVertexArray(VAOs[4]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glUseProgram(shaderProgram6);
        glBindVertexArray(VAOs[5]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram7);
        glBindVertexArray(VAOs[6]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        glUseProgram(shaderProgram8);
        glBindVertexArray(VAOs[7]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(7, VAOs);
    glDeleteBuffers(7, VBOs);
    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);
    glDeleteProgram(shaderProgram3);
    glDeleteProgram(shaderProgram4);
    glDeleteProgram(shaderProgram5);
     glDeleteProgram(shaderProgram6);
      glDeleteProgram(shaderProgram7);
       glDeleteProgram(shaderProgram8);
    

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
//
//int main() {
//	std::cout << "h" << std::endl;
//}




//                                                      rotate the photo in 360 angle 

#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"renderer.h"

#include "vertex_buffer.h"
#include"vertex_buffer_layout.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include"shader.h"
#include"texture.h"

#include"glm/glm.hpp"                       //  glm 🡆header only library
#include"glm/gtc/matrix_transform.hpp"      //


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    //window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK) {
        std::cout << "rrr" << std::endl;
        return -1;
    }

    std::cout << (const char*)glGetString(GL_VERSION) << std::endl;

    //--------------------------------------------------------------
{
    float position[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f

    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };  

    GLCall(glEnable(GL_BLEND));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
 
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    VertexBuffer vb(position, 4 * 4 * sizeof(float));

    VertexArray va;

    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);

    va.AddBuffer(vb,layout);

    //glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f,-1.0f,1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);


    //glm::vec4 vp(100.0f, 100.0f, 0.0, 1.0);

    glm::mat4 mvp = proj * view * model;



    Shader shader("res/shaders/basic.shader");
    shader.Bind();
    shader.Setuniform4f("u_colour", 0.2, 0.3, 0.8, 1.0);
    shader.SetuniformMat4f("u_MVP", mvp);





    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    indexBuffer ib(indices, 6);
	//Texture texture("res/textures/c_image.png");
    Texture texture("res/textures/wp425495.png");

    shader.Setuniform1i("u_texture", 0);
    texture.Bind();

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
    Renderer renderer;

    double lastMouseX = 0.0, lastMouseY = 0.0;
    float rotX = 0.0f, rotY = 0.0f;
    bool mousePressed = false;
    

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

		renderer.Clear();


        
        shader.Bind();
        //float angle = (float)glfwGetTime();
        //model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
        //glm::mat4 mvp = proj * view * model;
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (!mousePressed) {
                lastMouseX = mouseX;
                lastMouseY = mouseY;
                mousePressed = true;
            }
            rotY += (float)(mouseX - lastMouseX) * 0.01f;
            rotX += (float)(mouseY - lastMouseY) * 0.01f;
            lastMouseX = mouseX;
            lastMouseY = mouseY;
        }
        else {
            mousePressed = false;
        }

        model = glm::rotate(glm::mat4(1.0f), rotY, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, rotX, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 mvp = proj * view * model;
        shader.SetuniformMat4f("u_MVP", mvp);

 

        //glBegin(GL_TRIANGLES);
        //glVertex2f(-0.5, -0.5);
        //glVertex2f(0.0, 0.5);
        //glVertex2f(0.5, -0.5);
        //glEnd();
             
        //glDrawArrays(GL_TRIANGLES,0,6);//this is to issue a draw call the buffer. this u do that u should not have an index buffer
        renderer.Draw(va,ib,shader);
        // glBindBuffer(GL_ARRAY_BUFFER, buffer); 🡆this line going to be the draw call going to draw the triangle. in opengl u have u select or bind it is a state machine


//glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,nullptr);// it use with an index buffer

/* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

}

    glfwTerminate();
    return 0;
}

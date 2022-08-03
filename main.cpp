#include<glad/glad.h>
#include "File_M.h"
#include "Texture.h"
#include "Game.h"
#include<GLFW/glfw3.h>
#include<iostream>

const unsigned int SW = 800;
const unsigned int SH = 600;
Game Breakout(800,600);
float deltaTime = 0.0f;
float lastTime  = 0.0f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Breakout.keys[key] = true;
        else if (action == GLFW_RELEASE)
            Breakout.keys[key] = false;
    }
}

void fsc(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int main(int argc,char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);
    GLFWwindow *window = glfwCreateWindow(800,600,"ok",NULL,NULL);
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        return -1;
    }
    glfwSetKeyCallback(window,key_callback);
    glfwSetFramebufferSizeCallback(window,fsc);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    Breakout.init();
    while(!glfwWindowShouldClose(window))
    {
        glm::mat4 projection = glm::ortho(0.0f,800.0f,600.0f,0.0f,-1.0f,1.0f);
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        glfwPollEvents();
        Breakout.ProcessInput(deltaTime);
        Breakout.Update(deltaTime);

        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        Breakout.Render();

        glfwSwapBuffers(window);
    }


}

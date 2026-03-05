#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

const int WIDTH = 900;
const int HEIGHT = 700;

float A = 0.0f;
float B = 0.0f;

void framebuffer_size_callback(GLFWwindow* window,int w,int h)
{
    glViewport(0,0,w,h);
}

void drawDonut()
{
    const char* shades = ".,-~:;=!*#$@";

    glBegin(GL_POINTS);

    for(float j=0;j<6.28;j+=0.07)
    {
        for(float i=0;i<6.28;i+=0.02)
        {
            float c = sin(i);
            float d = cos(j);
            float e = sin(A);
            float f = sin(j);
            float g = cos(A);
            float h = d + 2;

            float D = 1/(c*h*e + f*g + 5);

            float l = cos(i);
            float m = cos(B);
            float n = sin(B);

            float t = c*h*g - f*e;

            float x = (l*h*m - t*n);
            float y = (l*h*n + t*m);
            float z = D*5;

            int N = 8*((f*e-c*d*g)*m - c*d*e - f*g - l*d*n);

            float brightness = (N>0?N:0)/11.0f;

            glColor3f(brightness,brightness,brightness);

            glVertex3f(x*3,y*3,z);
        }
    }

    glEnd();
}

int main()
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"ASCII Style OpenGL Donut",NULL,NULL);

    if(!window)
    {
        std::cout<<"Window failed\n";
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"GLAD failed\n";
        return -1;
    }

    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
    glPointSize(3);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float ratio = (float)WIDTH/HEIGHT;
        glFrustum(-ratio,ratio,-1,1,1,100);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0,0,-10);

        drawDonut();

        // slower spin like ASCII version
        A += 0.01f;
        B += 0.005f;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
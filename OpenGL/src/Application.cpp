#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>

#include "Texture.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"


int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);//����֡��ʹ�䴹ֱͬ��


    if (glewInit() != GLEW_OK)
    {
        std::cout << "glewInit err!" << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            100.0f, 100.0f, 0.0f, 0.0f,//0
            200.0f, 100.0f, 1.0f, 0.0f,//1
            200.0f, 200.0f, 1.0f, 1.0f,//2
            100.0f, 200.0f, 0.0f, 1.0f//3
        };

        unsigned int indices[] =
        {
            0,1,2,
            2,3,0
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));
        //����һ���������鲢��
        VertexArray va;

        //����һ�����㻺����
        VertexBuffer vb(positions, sizeof(positions));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        //�������������GPU
        IndexBuffer ib(indices, 6);
        //�������������GPU
        const std::string& filepath = "res/shaders/Basic.shader";
        Shader shader(filepath);//һ�Ž�ȥ�����캯�����Ѿ�������
		//����ͶӰ����
		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        //����һ����ͼ����
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0, 0));
        //ģ�;���
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0));
        glm::mat4 mvp = proj * view * model;
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        //shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		Texture texture("res/texture/ChernoLogo.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);//���
        //���
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;



        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
            //���°�
            renderer.Draw(va, ib, shader);

            //ʹ��ɫ��ʼ�任
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            if (r > 1.0f)
            {
                increment = -0.05f;
            }
            else if (r < 0.0f)
            {
                increment = 0.05f;
            }
            r += increment;
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
} 
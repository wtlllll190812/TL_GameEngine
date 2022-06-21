#pragma once
#include <GLFW/glfw3.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>


class Mesh
{
public:
    GLuint VAO;
    GLuint VBO;
    //GLuint EBO;

	Mesh(int, std::vector<int>,GLfloat[],int);
	~Mesh();
private:
	
};

Mesh::Mesh(int sum,std::vector<int> settings,GLfloat vertices[],int size)
{
    //���㻺��
    glGenBuffers(1, &VBO);//���û���ID
    //glGenBuffers(1, &EBO);
    //�����������
    glGenVertexArrays(1, &VAO);//���û���ID

    glBindVertexArray(VAO);//�󶨶����������

    glBindBuffer(GL_ARRAY_BUFFER, VBO);//�󶨻������
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);//�������ݵ�����
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    int offset=0;
    for (size_t i = 0; i < settings.size(); i++)
    {
        glVertexAttribPointer(i, settings[i], GL_FLOAT, GL_FALSE, sum * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));//���ý����������ݵķ�ʽ
        glEnableVertexAttribArray(i);//���ö�������
        offset += settings[i];
    }
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
}
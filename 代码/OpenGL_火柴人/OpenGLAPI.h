#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <json/json.h>

#include <QtGui/qvector3d.h>

#include "Camera.h"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <direct.h>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;       
};

class OpenGLAPI {
private:
	GLFWwindow* window;
	Shader ourShader;
	std::vector<std::vector<QVector3D>> gPosition1;
	std::vector<std::vector<QVector3D>> gPosition2;
	int gFrame;
	//�����û����룬w,s,a,d,��,��������꣬�������λ��
	void processInput(GLFWwindow *window);
	//��ȡ.json�ļ��е�λ����Ϣ
	bool ReadPosition(const char* lFilename, std::vector<std::vector<QVector3D>>& lpos);
	//����õ��������ؽڵ㣬�õ�����׶������������꣬�������������
	void processVertice(std::vector<Vertex> &vertices, QVector3D base, QVector3D front);
	//�ֱ���Vnect�õ��ĸ���������
	void processVertice_Vnect(std::vector<Vertex> &vertices, std::vector<std::vector<QVector3D>>& lpos);
	//�ֱ���OpenMMD�õ��ĸ���������
	void processVertice_OpenMMD(std::vector<Vertex> &vertices, std::vector<std::vector<QVector3D>>& lpos);
	//��ʼ��
	void initialize();


public:
	//������3D����ʱʹ�õĹ��캯��
	OpenGLAPI(const char * lfilename) {
		if (ReadPosition(lfilename, gPosition1)) {
			initialize();
		}
	}
	//��������3D����ʱʹ�õĹ��캯��
	OpenGLAPI(const char * lfilename1, const char * lfilename2) {
		if (ReadPosition(lfilename1, gPosition1) && ReadPosition(lfilename2, gPosition2)) {
			initialize();
		}
	}
	//������Vnect�ܳ�����3D����
	void singleVideo_Vnect();
	//������OpenMMD�ܳ�����3D����
	void singleVideo_OpenMMD();
	//��������Vnect�ܳ�����3D����
	void doubleVideo_Vnect();
	//��������OpenMMD�ܳ�����3D����
	void doubleVideo_OpenMMD();
};

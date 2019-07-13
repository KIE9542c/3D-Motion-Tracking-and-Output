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
#include "MotionContrastor.h"

#include <iostream>
#include <fstream>
#include <direct.h>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;       
};
struct Vertex2 {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Color;
};

class OpenGLAPI {
private:
	GLFWwindow* window;
	Shader ourShader;
	const char * filename1;
	const char * filename2;
	std::vector<std::vector<QVector3D>> gPosition1;
	std::vector<std::vector<QVector3D>> gPosition2;
	MotionContrastor motionContrastor;
	int gFrame;
	//处理用户输入，w,s,a,d,↑,↓，与鼠标，控制相机位置
	void processInput(GLFWwindow *window);
	//读取.json文件中的位置信息
	bool ReadPosition(const char* lFilename, std::vector<std::vector<QVector3D>>& lpos);
	//处理得到的两个关节点，得到四棱锥的五个顶点坐标，将其存入数组中
	void processVertice(std::vector<Vertex> &vertices, QVector3D base, QVector3D front);
	//分别处理Vnect得到的各个骨骼点
	void processVertice_Vnect(std::vector<Vertex> &vertices, std::vector<std::vector<QVector3D>>& lpos);
	//分别处理OpenMMD得到的各个骨骼点
	void processVertice_OpenMMD(std::vector<Vertex> &vertices, std::vector<std::vector<QVector3D>>& lpos);
	//处理得到的两个关节点，得到四棱锥的五个顶点坐标，将其存入数组中
	void processVertice2(std::vector<Vertex2> &vertices, QVector3D base, QVector3D front,glm::vec3 color);
	//分别处理Vnect得到的各个骨骼点
	void processVertice_Vnect2(std::vector<Vertex2> &vertices, std::vector<std::vector<QVector3D>>& lpos, int frame,std::vector<glm::vec3>color);
	//分别处理OpenMMD得到的各个骨骼点
	void processVertice_OpenMMD2(std::vector<Vertex2> &vertices, std::vector<std::vector<QVector3D>>& lpos, int frame, std::vector<glm::vec3>color);
	//初始化
	void initialize();


public:
	//处理单个3D坐标时使用的构造函数
	OpenGLAPI(const char * lfilename) {
		if (ReadPosition(lfilename, gPosition1)) {
			initialize();
		}
	}
	//处理两个3D坐标时使用的构造函数
	OpenGLAPI(const char * lfilename1, const char * lfilename2) {
		initialize();
		filename1 = lfilename1;
		filename2 = lfilename2;
	}
	//处理单个Vnect跑出来的3D坐标
	void singleVideo_Vnect();
	//处理单个OpenMMD跑出来的3D坐标
	void singleVideo_OpenMMD();
	//处理两个Vnect跑出来的3D坐标
	void doubleVideo_Vnect();
	//处理两个OpenMMD跑出来的3D坐标
	void doubleVideo_OpenMMD();
	//获取姿态对比结果
	MotionContrastor getMotionContrastor() { return motionContrastor; }
};

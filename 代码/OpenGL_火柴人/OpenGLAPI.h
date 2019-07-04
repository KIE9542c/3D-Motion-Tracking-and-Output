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

class OpenGLAPI {
private:
	GLFWwindow* window;
	Shader ourShader;
	std::vector<std::vector<QVector3D>> gPosition1;
	std::vector<std::vector<QVector3D>> gPosition2;
	int gFrame;
	void processInput(GLFWwindow *window);
	bool ReadPosition(const char* lFilename, std::vector<std::vector<QVector3D>>& lpos);
	void processVertice(std::vector<glm::vec3> &vertices, QVector3D base, QVector3D front);
	void processVertice_Vnect(std::vector<glm::vec3> &vertices, std::vector<std::vector<QVector3D>>& lpos);
	void processVertice_OpenMMD(std::vector<glm::vec3> &vertices, std::vector<std::vector<QVector3D>>& lpos);
	void initialize();


public:
	OpenGLAPI(const char * lfilename) {
		if (ReadPosition(lfilename, gPosition1)) {
			initialize();
		}
	}
	OpenGLAPI(const char * lfilename1, const char * lfilename2) {
		if (ReadPosition(lfilename1, gPosition1) && ReadPosition(lfilename2, gPosition2)) {
			initialize();
		}
	}
	void singleVideo_Vnect();
	void singleVideo_OpenMMD();
	void doubleVideo_Vnect();
	void doubleVideo_OpenMMD();
};

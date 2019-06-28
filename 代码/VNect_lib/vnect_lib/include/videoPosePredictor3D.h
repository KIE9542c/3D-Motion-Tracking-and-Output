#pragma once
#include <vnectUtils.hpp>
#include <string>
#include <Json.h>
#include <Windows.h>
#include <atlconv.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mShader.h"
#include "mCamera.h"
#include "mDefs.h"
#include "mMeshRender.h"


bool isMousePressed;
double curX, curY;
double initX, initY;
glm::mat4 rotateMat;
glm::mat4 model;

class __declspec(dllexport) mVideoPosePredictor3D
{
private:

	const std::string model_path;
	const std::string prototxt_path;
	mVNectUtils predictor;
	cv::VideoCapture video;


public:
	//model_path: caffemodel path,  prototxt_path: prototxt path
	mVideoPosePredictor3D(const std::string& model_path, const std::string& prototxt_path);
	
	//begin predict all the video.
	//video_path: video path
	//output_position: the output 3d positions
	//is_relative: is relative to the hip
	void predict(const std::string& video_path, const string& shader_dir, const string& mesh_dir, std::vector<std::vector<float>>& output_postition, const bool& is_relative = false, const bool& isShow = true);

	//begin write the positions to json file
	//path : json path
	//output_position: the position you want to write
	void writePositionToJson(const std::string& path, const std::vector<std::vector<float>>& output_postition);
private:
	void joints_scale_3d(const std::vector<float>& joints3d, std::vector<float>& result);

};

void SetOpenGLState();
GLFWwindow* InitWindow(float, float);
void drawPoint(cv::Mat& img, const std::vector<float>& pos);
void error_callback(int error, const char* description);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_move_callback(GLFWwindow* window, double x, double y);




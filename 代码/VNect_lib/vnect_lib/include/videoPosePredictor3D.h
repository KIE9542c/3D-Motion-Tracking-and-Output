#pragma once
#include <vnectUtils.hpp>
#include <string>
#include <Json.h>
#include <Windows.h>
#include <atlconv.h>

#include <glad/glad.h>
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
extern "C"
{
#include <libavformat\avformat.h>
};
struct coordpoint
{
	int x, y, z;
};
struct param_t
{
	const bool* is_relative;
	const bool* is_show;
	const char* shader_dir;
	const char* mesh_dir;
	const char* video_path;
	mVNectUtils *predictor;
	vector<vector<float>>* positions;
};



static bool isMousePressed;
static double curX, curY;
static double initX, initY;
static glm::mat4 rotateMat;
static glm::mat4 model;
static const double font_scale = 1;
static const int thickness = 1;
static const int font_face = cv::FONT_HERSHEY_COMPLEX;
static int text_line;
static char txt_buffer[10];

class __declspec(dllexport) mVideoPosePredictor3D
{
private:

	const std::string model_path;
	const std::string prototxt_path;
	mVNectUtils predictor;


public:
	//model_path: caffemodel path,  prototxt_path: prototxt path
	mVideoPosePredictor3D(const std::string& model_path, const std::string& prototxt_path);
	
	//begin predict all the video.
	//video_path: video path
	//output_position: the output 3d positions
	//is_relative: is relative to the hip
	void predict(const std::string& video_path, const string& shader_dir, const string& mesh_dir, std::vector<std::vector<float>>& output_postition, const bool& is_relative = false);

	//begin write the positions to json file
	//path : json path
	//output_position: the position you want to write
	void writePositionToJson(const std::string& path, const std::string& video_path, const std::vector<std::vector<float>>& output_postition);
	void predict_t(const string& video_path, const string& shader_dir, const string& mesh_dir, std::vector<std::vector<float>> output, const bool& is_relative, const bool& is_show);
	void predict_notShow(const std::string& video_path, const string& shader_dir, const string& mesh_dir, std::vector<std::vector<float>>& output_postition, const bool& is_relative = false);

private:
	float resize_ratio(const float& picture_width, const float& picture_height, const float& default_width, const float& default_height);


};

void SetOpenGLState();
GLFWwindow* InitWindow(float, float);
void drawPoint(cv::Mat& img, const std::vector<float>& pos);
void drawPoint(cv::Mat& img, const std::vector<float>& pos, cv::Rect r);
void drawText(cv::Mat& img, const string& text);
void error_callback(int error, const char* description);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_move_callback(GLFWwindow* window, double x, double y);
DWORD WINAPI ThreadProFunc(LPVOID lpParam);
void joints_scale_3d(const std::vector<float>& joints3d, std::vector<float>& result);
double get_rotation(AVStream* st);

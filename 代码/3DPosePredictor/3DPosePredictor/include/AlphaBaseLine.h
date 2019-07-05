#pragma once
#include <torch/torch.h>
#include <torch/script.h>
#include "Darknet.h"
#include <iostream>
#include <chrono>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mShader.h"
#include "mCamera.h"
#include "mMeshRender.h"
#include <3d_baseLine_predictor.h>
#include <Json.h>
namespace alphaBaseline
{
	class __declspec(dllexport) AlphaBaseline
{
private:
	const float means_2d[32] = { 534.23620678, 425.88147731, 533.39373118,425.69835782,534.39780234,
	497.43802989,532.48129382, 569.04662344, 535.29156558, 425.73629462,
	532.76756177,496.47315471, 530.88803412, 569.60750683, 535.75344606,
	331.22677323,536.33800053, 317.44992858, 536.71629464, 269.11969467,
	536.36740264,330.27798906, 535.85669709, 374.59944401, 534.70288482,
	387.35266055, 534.99202566, 331.77346527, 534.61130808, 373.81679139,
	535.21529192, 379.50779675 };

	const float stds_2d[32] = { 107.37361012,  61.63490959, 114.89497053,  61.91199702 ,117.27565511,
	  50.22711629, 118.89857526  ,55.00005709, 102.91089763  ,61.33852088,
	 106.66944715 , 47.96084756 ,108.13481259 , 53.60647266 ,110.56227428,
	  72.9166997  ,110.84492972  ,76.09916643 ,115.08215261  ,82.92943734,
	 105.04274864  ,72.84070269 ,106.3158104   ,73.21929021 ,108.08767528,
	  82.4948776  ,124.31763034 , 73.34214366 ,132.80917569,  76.37108859,
	 131.60933137 , 88.82878858 };

	const double means_3d[48] = { -2.55652589e-01, -7.11960573e+00, -9.81433058e-01, -5.65463051e+00,
	  3.19636009e+02,  7.19329269e+01, -1.01705840e+01,  6.91147892e+02,
	  1.55352986e+02,  2.55651315e-01 , 7.11954604e+00,  9.81423860e-01,
	 -5.09729780e+00,  3.27040413e+02,  7.22258095e+01, -9.99656606e+00,
	  7.08277383e+02,  1.58016408e+02,  2.90583676e+00, -2.11363307e+02,
	 -4.74210915e+01,  5.67537804e+00, -4.35088906e+02, -9.76974016e+01,
	  5.93884964e+00, -4.91891970e+02, -1.10666618e+02,  7.37352083e+00,
	 -5.83948619e+02 ,-1.31171400e+02,  5.41920653e+00 ,-3.83931702e+02,
	 -8.68145417e+01,  2.95964663e+00, -1.87567488e+02, -4.34536934e+01,
	  1.26585822e+00, -1.20170579e+02, -2.82526049e+01,  4.67186639e+00,
	 -3.83644089e+02, -8.55125784e+01,  1.67648571e+00, -1.97007177e+02,
	 -4.31368363e+01,  8.70569014e-01, -1.68664569e+02 ,-3.73902498e+01 };

	const double stds_3d[48] = { 110.72243952, 22.38817617,  72.46294422, 158.56311079, 189.33832207,
	 208.80479146, 191.79935232, 243.20061683, 247.56193296, 110.72180724,
	  22.38805433,  72.46252568, 158.80454093, 199.77187809, 214.70629784,
	 180.01944122, 250.52739313, 248.53247138,  52.10694018,  52.11405526,
	  69.08241484,  95.15366544, 101.3303182 , 128.99732515, 117.42457701,
	 126.48468958, 164.65090648, 123.60296575, 130.8553891,  164.33336501,
	 146.02231893,  97.07955985, 139.52731253, 243.47531766, 129.82248593,
	 202.30181233, 244.68770048, 215.01816412, 239.38234725, 138.76084446,
	 100.89260001, 142.44109658, 236.87528987, 144.91219013, 209.80829096,
	 244.00694913, 239.7502835,  255.20583986 };
	const int mapping1[16] = { -1,12,14,16,11,13,15,-1,-1,0,5,7,9,6,8,10 };
	const int mapping2[16] = { 6,2,1,0,3,4,5,8,7,9,13,14,15,12,11,10 };
	const std::vector<unsigned int> indics = { 0,1,
									1,2,
									2,3,

									0,4,
									4,5,
									5,6,

									0,7,
									7,8,
									8,9,
									9,10,

									8,11,
									11,12,
									12,13,

									8,14,
									14,15,
									15,16 };
	const double font_scale = 1;
	const int thickness = 1;
	const int font_face = cv::FONT_HERSHEY_COMPLEX;
	//const float det_width_alpha = 256, det_height_alpha = 320, fea_width_alpha = 64, fea_height_alpha = 80;//change....................
	//const float det_width = 192, det_height = 256, fea_width = 48, fea_height = 64;//change....................
	const float det_width = 288, det_height = 384, fea_width = 72, fea_height = 96;
	int text_line;
	const int input_image_size = 256;
	char txt_buffer[20];
	Darknet net;
	std::shared_ptr<torch::jit::script::Module> module;
	BaseLinePredictor baseline;
	torch::DeviceType device_type;

public:
	AlphaBaseline(const string& yolo_cfg, const string& yolo_weight, const string& alpahaPose_path, const string& baseline_path);
	int predict(const string& video_path, const string& shader_dir, const string& mesh_dir, std::vector<std::vector<float>> output);
	void writePositionToJson(const std::string& path, const std::vector<std::vector<float>>& output_postition);
	int predict_notShow(const string& video_path, const string& shader_dir, const string& mesh_dir, std::vector<std::vector<float>> position_3d);

private:
	float resize_ratio(const float& picture_width, const float& picture_height, const float& default_width, const float& default_height);
	void drawPoint(cv::Mat& img, const std::vector<float>& pos, const int& joint_num);
	void drawTxt(cv::Mat& img, const string& txt);
};




	bool isMousePressed = false;
	double initX, initY;
	double curX, curY;
	glm::mat4 rotateMat = glm::mat4(1.0);
	glm::mat4 model = glm::mat4(1.0);
	void mouse_move_callback(GLFWwindow* window, double x, double y);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void SetOpenGLState();
	void error_callback(int error, const char* description);
	GLFWwindow* InitWindow(float wndWidth, float wndHeight);
}
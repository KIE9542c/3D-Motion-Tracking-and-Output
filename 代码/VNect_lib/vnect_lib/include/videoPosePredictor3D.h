#pragma once
#include <vnectUtils.hpp>
#include <string>
#include <Json.h>
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
	void predict(const std::string& video_path,std::vector<std::vector<float>>& output_postition,const bool& is_relative=false);
	
	//begin write the positions to json file
	//path : json path
	//output_position: the position you want to write
	void writeToJson(const std::string& path, const std::vector<std::vector<float>>& output_postition);
private:
	void joints_scale_3d(const std::vector<float>& joints3d, std::vector<float>& result);
};
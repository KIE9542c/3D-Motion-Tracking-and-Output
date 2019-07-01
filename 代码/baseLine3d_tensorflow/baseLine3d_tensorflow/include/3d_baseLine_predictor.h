#pragma once

#include <3d_baseLine_loader.h>

#ifdef _EXPORTDLL  
#define DllExport    __declspec(dllexport)  
#else  
#define DllExport    __declspec(dllimport)  
#endif 

class DllExport BaseLinePredictor
{
private:
	const std::string IS_TRAINING = "isTrainingflag:0";
	const std::string DROPOUT_FLAG = "dropout_keep_prob:0";
	const std::string INPUT_NAME = "inputs/enc_in:0";
	const std::string OUTPUT_NAME = "linear_model/add_1:0";
	const bool is_train = false;
	const float dropout = 1.0;
	Session* session;
	tf_model::BaseLineModelLoader model;
	bool is_opened = false;
public:
	BaseLinePredictor(const string& model_path);
	int predict(const std::vector<float>& input, std::vector<float>& output);
	bool isOpened();
};

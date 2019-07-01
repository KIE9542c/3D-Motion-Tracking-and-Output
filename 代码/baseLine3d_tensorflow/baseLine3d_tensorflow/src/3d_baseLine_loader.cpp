#include <iostream>
#include <vector>
#include <map>
#include "3d_baseLine_loader.h"

using namespace tensorflow;

namespace tf_model {

	/**
	 * ANNFeatureAdapter Implementation
	 * */
	BaseLineFeatureAdapter::BaseLineFeatureAdapter() {

	}

	BaseLineFeatureAdapter::~BaseLineFeatureAdapter() {

	}

	/*
	 * @brief: Feature Adapter: convert 1-D double vector to Tensor, shape [1, ndim]
	 * @param: std::string tname, tensor name;
	 * @parma: std::vector<double>*, input vector;
	 * */
	void BaseLineFeatureAdapter::assign(const std::string& tname, const std::vector<float>& vec) {
		//Convert input 1-D double vector to Tensor
		int ndim = vec.size();
		if (ndim == 0) {
			std::cout << "WARNING: Input Vec size is 0 ..." << std::endl;
			return;
		}
		// Create New tensor and set value
		Tensor x(tensorflow::DT_FLOAT, tensorflow::TensorShape({ 1, ndim })); // New Tensor shape [1, ndim]
		auto x_map = x.tensor<float, 2>();
		for (int j = 0; j < ndim; j++) {
			x_map(0, j) = vec[j];
		}
		// Append <tname, Tensor> to input
		input.push_back(std::pair<std::string, tensorflow::Tensor>(tname, x));
	}

	void BaseLineFeatureAdapter::assign(const std::string& tname, const bool& flag)
	{
		Tensor x(DT_BOOL, TensorShape());
		x.scalar<bool>()() = flag;
		input.push_back(std::pair<std::string, tensorflow::Tensor>(tname, x));
	}

	void BaseLineFeatureAdapter::assign(const std::string& tname, const float& value)
	{
		Tensor x(DT_FLOAT, TensorShape());
		x.scalar<float>()() = value;
		input.push_back(std::pair<std::string, tensorflow::Tensor>(tname, x));
	}

	/**
	 * ANN Model Loader Implementation
	 * */
	BaseLineModelLoader::BaseLineModelLoader() {

	}

	BaseLineModelLoader::~BaseLineModelLoader() {

	}

	/**
	 * @brief: load the graph and add to Session
	 * @param: Session* session, add the graph to the session
	 * @param: model_path absolute path to exported protobuf file *.pb
	 * */

	int BaseLineModelLoader::load(tensorflow::Session* session, const std::string model_path) {
		//Read the pb file into the grapgdef member
		tensorflow::Status status_load = ReadBinaryProto(Env::Default(), model_path, &graphdef);
		if (!status_load.ok()) {
			std::cout << "ERROR: Loading model failed..." << model_path << std::endl;
			std::cout << status_load.ToString() << "\n";
			return -1;
		}

		// Add the graph to the session
		tensorflow::Status status_create = session->Create(graphdef);
		if (!status_create.ok()) {
			std::cout << "ERROR: Creating graph in session failed..." << status_create.ToString() << std::endl;
			return -1;
		}
		return 0;
	}


	/**
	 * @brief: Making new prediction
	 * @param: Session* session
	 * @param: FeatureAdapterBase, common interface of input feature
	 * @param: std::string, output_node, tensorname of output node
	 * @param: double, prediction values
	 * */

	int BaseLineModelLoader::predict(tensorflow::Session* session, const FeatureAdapterBase& input_feature,
		const std::string& output_node, std::vector<float>& result) {
		// The session will initialize the outputs
		std::vector<tensorflow::Tensor> outputs;         //shape  [batch_size]

		// @input: vector<pair<string, tensor> >, feed_dict
		// @output_node: std::string, name of the output node op, defined in the protobuf file
		tensorflow::Status status = session->Run(input_feature.input, { output_node }, {}, &outputs);
		if (!status.ok()) {
			std::cout << "ERROR: prediction failed..." << status.ToString() << std::endl;
			return -1;
		}

		Tensor t = outputs[0];                   // Fetch the first tensor
		int ndim = t.shape().dims();             // Get the dimension of the tensor
		auto tmap = t.tensor<float, 2>();        // Tensor Shape: [batch_size, target_class_num]
		int output_dim = t.shape().dim_size(1);  // Get the target_class_num from 1st dimension


		result.clear();
		for (int j = 0; j < output_dim; j++) {
			result.push_back(tmap(0, j));
		}
		return 0;
	}

}
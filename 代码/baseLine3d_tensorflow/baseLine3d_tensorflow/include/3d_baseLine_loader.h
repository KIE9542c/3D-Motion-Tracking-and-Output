#ifndef CPPTENSORFLOW_3D_MODEL_LOADER_H
#define CPPTENSORFLOW_3D_MODEL_LOADER_H

#include "model_loader_base.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/platform/env.h"

using namespace tensorflow;

#ifdef _EXPORTDLL  
#define DllExport    __declspec(dllexport)  
#else  
#define DllExport    __declspec(dllimport)  
#endif 
namespace tf_model {

	/**
	 * @brief: Model Loader for Feed Forward Neural Network
	 * */
	class DllExport  BaseLineFeatureAdapter : public FeatureAdapterBase {
	public:

		BaseLineFeatureAdapter();

		~BaseLineFeatureAdapter();

		void assign(const std::string& tname, const std::vector<float>&) override; // (tensor_name, tensor)
		void assign(const std::string& tname, const bool&) override;
		void assign(const std::string& tname, const float&) override;
	};

	class DllExport BaseLineModelLoader : public ModelLoaderBase {
	public:
		BaseLineModelLoader();

		~BaseLineModelLoader();

		int load(tensorflow::Session*, const std::string) override;    //Load graph file and new session

		int predict(tensorflow::Session*, const FeatureAdapterBase&, const std::string&, std::vector<float>&) override;

	};

}


#endif 
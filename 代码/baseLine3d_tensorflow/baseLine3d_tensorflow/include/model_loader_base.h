#ifndef CPPTENSORFLOW_MODEL_LOADER_BASE_H
#define CPPTENSORFLOW_MODEL_LOADER_BASE_H
#include <iostream>
#include <vector>
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
 * Base Class for feature adapter, common interface convert input format to tensors
 * */
    class DllExport FeatureAdapterBase{
    public:
        FeatureAdapterBase() {};
 
        virtual ~FeatureAdapterBase() {};
 
        virtual void assign(const std::string&, const std::vector<float>&) = 0;  // tensor_name, tensor_double_vector
		virtual void assign(const std::string&, const bool&) = 0;
		virtual void assign(const std::string&, const float&) = 0;
        std::vector<std::pair<std::string, tensorflow::Tensor> > input;
 
    };
 
    class DllExport ModelLoaderBase {
    public:
 
        ModelLoaderBase() {};
 
        virtual ~ModelLoaderBase() {};
 
        virtual int load(tensorflow::Session*, const std::string) = 0;     //pure virutal function load method
 
        virtual int predict(tensorflow::Session*, const FeatureAdapterBase&, const std::string&, std::vector<float>& ) = 0;
 
        tensorflow::GraphDef graphdef; //Graph Definition for current model
 
    };
 
}
 
#endif //CPPTENSORFLOW_MODEL_LOADER_BASE_H
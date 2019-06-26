#ifndef VNECT_UTILS
#define VNECT_UTILS
#include "mCaffePredictor.hpp"
#include "oneEuro.hpp"
#include "vnectJointsInfo.hpp"

// According to the paper, I got that the image is 
// represented by joint angle \theta and camera location d
// I will maintain a bone length array. 
// The length is 3D length  
// When fitting, I find something strange, the fitting process doesn't change the z of d, only changed the so called "angles"


class __declspec(dllexport) mVNectUtils: public mCaffePredictor 
{
protected:
    virtual void preprocess(const cv::Mat & img, std::vector<cv::Mat> * input_data);
    virtual void wrapInputLayer(std::vector<cv::Mat> * input_data);
private:
    double _time_stamp; // used for filter
    bool _is_tracking;
    std::vector<float> _scales;
    cv::Size _box_size; 
    bool _is_first_frame;
    std::vector<int> _crop_rect;
    std::vector<int> _pad_offset;
    int _crop_size;
    float _crop_scale;
    // The scale of the input and the output. Now it's 8.
    float _hm_factor; 
	float* joints_2d[3];
    float * joints_3d[3];
    // Used for fitting! P^G_t P^G_t-1 P^G_t-2 and the same order of global_d
	float* joint_angles[3];
	float* global_d[3];
    one_euro_filter<float> *mFilters[joint_num*2];
    one_euro_filter<float> *mFilters_3d[joint_num*3];
    one_euro_filter<float> *mFilters_global[joint_num*3];

    cv::Mat padImage(const cv::Mat &img, cv::Size box_size);
    std::vector<int> crop_pos(bool type, int crop_offset=0);
    // Used to get the 3d location of all points by \theta and d
public:
    ~mVNectUtils(); 

	//model_path: caffemodel path, 
	//prototxt_path: prototxt path
    mVNectUtils(const std::string &model_path, const std::string &prototxt_path, const std::string &mean_path="");
    
	//predict one frame
	//img: one frame, 
	//joint2d:the output 2d positions
	//joints3d: the output 3d positions
	//is_relative: is relative to the hip
	void predict(const cv::Mat &img, std::vector<float>& joint2d, std::vector<float>& joints3d,const bool& is_relative=false);
};

#endif

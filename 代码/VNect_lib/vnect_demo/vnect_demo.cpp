#include <vnectUtils.hpp>
#include <videoPosePredictor3D.h>
int main()
{
	int tW = 320, tH = 256;
	mVideoPosePredictor3D predictor("../caffemodel/vnect_model.caffemodel", "../caffemodel/vnect_net.prototxt");
	std::vector<std::vector<float>> positions;
	predictor.predict("D:\\Dataset\\vgaPose3d_stage1_coco19\\vga_10_02.mp4",positions,true);


	return 0;
}
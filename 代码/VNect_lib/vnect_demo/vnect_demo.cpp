#include <videoPosePredictor3D.h>
int main()
{
	int tW = 320, tH = 256;
	mVideoPosePredictor3D predictor("../caffemodel/vnect_model.caffemodel", "../caffemodel/vnect_net.prototxt");
	std::vector<std::vector<float>> positions;
	predictor.predict("D:\\Dataset\\20190625154359.mp4","D:\\Code\\C++\\Vnect_Caffe\\Vnect_Caffe\\shader","D:\\Code\\C++\\Vnect_Caffe\\Vnect_Caffe\\model",positions,true,true);
	predictor.writePositionToJson("D:\\Dataset\\a.json", positions);

	return 0;
}
#include "videoPosePredictor3D.h"

mVideoPosePredictor3D::mVideoPosePredictor3D(const std::string& model_path, const std::string& prototxt_path):model_path(model_path),prototxt_path(prototxt_path),predictor(model_path,prototxt_path)
{

}

void mVideoPosePredictor3D::predict(const std::string& video_path,std::vector<std::vector<float>>& output_postition, const bool& is_relative)
{
	video= cv::VideoCapture(video_path);
	std::vector<float> tmp;
	std::vector<float> tmp3d;
	if (video.isOpened())
	{
		int current_frame_id = 0;
		int total_frame = (int)video.get(CV_CAP_PROP_FRAME_COUNT);
		cv::Mat frame;
		do
		{
			if (!video.read(frame))
			{
				continue;
			}

			predictor.predict(frame, tmp, tmp3d,is_relative);
			std::vector<float> vertexs;
			joints_scale_3d(tmp3d, vertexs);
			output_postition.push_back(vertexs);

		}
		while (current_frame_id < total_frame);
	}

}

void mVideoPosePredictor3D::writeToJson(const std::string& path, const std::vector<std::vector<float>>& output_postition)
{
	writeToJson(path, output_postition);
}


void mVideoPosePredictor3D::joints_scale_3d(const std::vector<float>& joints3d, std::vector<float>& result)
{
	result.clear();
	int scale_size = 1;
	for (int i = 0; i < joint_num; ++i)
	{
		// here I need to normalize them
		//

		result.push_back(scale_size * static_cast<float>(joints3d[i * 3]));
		result.push_back(scale_size * static_cast<float>(joints3d[i * 3 + 1]));
		result.push_back(scale_size * static_cast<float>(joints3d[i * 3 + 2]));

		cout << joints3d[i * 3 + 0] << ", " << joints3d[i * 3 + 1] << ", " << joints3d[i * 3 + 2] << std::endl;
	}
}

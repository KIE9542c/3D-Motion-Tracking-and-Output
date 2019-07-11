#include <Json.h>
#include <mDefs.h>
#include <oneEuro.hpp>

__declspec(dllexport) void readFromJson(string path, std::vector<float>& result)
{
	result.clear();
	one_euro_filter<double>* mFilters_3d[3*17];
	for (int i = 0; i < 17; ++i) {
		mFilters_3d[3 * i] = new one_euro_filter<double>(one_euro_filter_frequency, 0.8, 0.4, 1);
		mFilters_3d[3 * i + 1] = new one_euro_filter<double>(one_euro_filter_frequency, 0.8, 0.4, 1);
		mFilters_3d[3 * i + 2] = new one_euro_filter<double>(one_euro_filter_frequency, 0.8, 0.4, 1);
	}


	float pose[45];
	// 以二进制形式读取json文件内容
	ifstream is(path, ios::in);

	if (!is.is_open())
	{
		cout << "open json file failed." << endl;
		return ;
	}
	JSONCPP_STRING errs;
	Json::CharReaderBuilder rbuilder;
	Json::Value root;


	bool parse_ok = Json::parseFromStream(rbuilder, is, &root, &errs);
	
	if (!parse_ok) {
		cout << "Parse json file error!" << endl;
	}
	else
	{
		Json::Value str = root["bodies"][0]["joints19"];
		for (int i = 0; i < 15; ++i)
		{
			pose[i * 3] = str[i * 4].asFloat();
			pose[i * 3+1] = str[i * 4+1].asFloat();
			pose[i * 3+2] = str[i * 4+2].asFloat();
		}
	}

	is.close();


	relativePose(pose);
	/*
	for (int i = 0; i < 17; ++i)
	{
		
			std::cout << (*mFilters_3d[3 * i])(pose[3 * i], 0) << ", "
				<< (*mFilters_3d[3 * i + 1])(pose[3 * i + 1], 0) << ", "
				<< (*mFilters_3d[3 * i + 2])(pose[3 * i + 2], 0) << std::endl;

			result.push_back(pose[3 * i]);
			result.push_back(pose[3 *i + 1]);
			result.push_back(pose[3 * i + 2]);
		
	}
	*/

	for (int i = 0; i < 17; ++i)
	{
		if (mappingFromVnect[i] != -1)
		{

			result.push_back((*mFilters_3d[3 * i])(pose[3 * mappingFromVnect[i]]/100.0+0.3  , 0));
			result.push_back((*mFilters_3d[3 * i+1])(-pose[3 * mappingFromVnect[i]+1] / 100.0, 0));
			result.push_back((*mFilters_3d[3 * i+2])(-pose[3 * mappingFromVnect[i]+2] / 100.0, 0));

		}
	}
	

}


void relativePose(float* origin)//change
{
	float oX = origin[2 * 3], oY = origin[2 * 3 + 1], oZ = origin[2 * 3 + 2];
	for (int i = 0; i < 15; ++i)
	{
		origin[i * 3] -= oX;
		origin[i * 3+1] -= oY;
		origin[i * 3+2] -= oZ;
	}
}

__declspec(dllexport) void writeToJson(const string& path, const std::vector<vector<float>>& positions)
{
	Json::Value root;
	Json::Value Json_body_object;
	for (int i = 0; i < positions.size(); ++i)
	{
		Json::Value Json_frame_object;
		Json_frame_object["frame"] = Json::Value(i);
		for (int j = 0; j < positions[i].size(); ++j)
		{
			Json_frame_object["position"].append(positions[i][j]);
		}
		Json_body_object.append(Json_frame_object);
	}
	root["bodies"]=Json_body_object;
	Json::StreamWriterBuilder  builder;
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	std::ofstream ofs;
	ofs.open(path, std::ios::out);
	writer->write(root, &ofs);
}


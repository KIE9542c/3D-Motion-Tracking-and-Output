#include <Json.h>
#include <mDefs.h>



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
	ofs.open(path, std::ios::app);
	writer->write(root, &ofs);
}


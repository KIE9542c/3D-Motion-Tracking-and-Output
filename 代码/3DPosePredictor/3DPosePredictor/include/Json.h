#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



void relativePose(float* origin);
//path: ���·��
//positions: 3d����
__declspec(dllexport) void writeToJson(const string& path, const std::vector<vector<float>>& positions);

#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


__declspec(dllexport) void readFromJson(string path, std::vector<float>& result);

void relativePose(float* origin);
//path: Êä³öÂ·¾¶
//positions: 3d×ø±ê
__declspec(dllexport) void writeToJson(const string& path, const std::vector<vector<float>>& positions);

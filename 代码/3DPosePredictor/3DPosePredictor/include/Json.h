#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



void relativePose(float* origin);
//path: Êä³öÂ·¾¶
//positions: 3d×ø±ê
__declspec(dllexport) void writeToJson(const string& path, const std::vector<vector<float>>& positions);

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <json\json.h>
#include <QtGui\qquaternion.h>
#include <QtGui\qvector3d.h>


class vmdWriter {

public:
	vmdWriter(std::string filename, std::string modelname, bool type);
	bool readPosition();
	bool isOpenMMD();
	void setBoneIndex();
	void transferCoordinate();
	void processRotaion(int index);
	void processPosition(int index);
	void writeFile(std::string filePath);
	void test();




private:
	char version[30] = "Vocaloid Motion Data 0002";
	char modelName[20];
	uint32_t keyFrameNumber;
	uint32_t frameTime;
	float position[4][3];  //0~3分别是其他骨骼，センター，左足IK，右足IK
	float rotation[10][4];  //0~9分别是センター，下半身，上半身，首，左腕，左ひじ，右腕，右ひじ，左足IK，右足IK
	uint32_t XCurve[4];
	uint32_t YCurve[4];
	uint32_t ZCurve[4];
	uint32_t RCurve[4];

	bool isopenMMD;  //true表示输入的骨骼坐标是openMMD导出的，否则为Vnect导出的
	int boneIndex[17];
	std::string fileName;
	std::vector<std::vector<QVector3D>> gPosition;




};
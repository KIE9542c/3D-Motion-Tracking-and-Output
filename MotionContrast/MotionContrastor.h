#pragma once
#include<iostream>
#include<cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <QtGui/qquaternion.h>
#include <QtGui/qvector3d.h>
#include <QtGui/qvector4d.h>
#include <QtGui/qmatrix4x4.h>
#include <json/json.h>
using namespace std;
class MotionContrastor {
public:
	bool getDistance(int Bones[]);
	bool contrast();
	bool readPosition(const char* File, vector<vector<QVector3D>>& gPosition);
	bool normalizeVnect();
	bool normalizeOpenMMD();
	bool cut();
	bool contrastVnect(const char* File1, const char* File2);
	bool contrastOpenMMD(const char* File1, const char* File2);
	int getcontrastPoint() { return  contrastPoint; };
public:
    struct pointOritation//节点方向，用来回溯每个W点
	{
		int frontI, frontJ;
	};
	
	vector<vector<int> >match;

private:
	vector<vector<QVector3D> > gPosition1;
	vector<vector<QVector3D> > gPosition2;
	vector<vector<int> > distance;
	static const int boneSize = 12;
	int vnectBones[boneSize] = {
		2,3,4,
		5,6,7,
		8,9,10,
		11,12,13
	};
	int mmdBones[boneSize] = {
		11,12,13,
		14,15,16,
		4,5,6,
		1,2,3
	};
	
	vector<vector<int> > dp;//dp[i][j]代表视频1第i帧与视频2第j帧的欧氏距离
	vector<vector<pointOritation> > pr;
	
	int length1;
	int length2;
	double contrastPoint;
	double unit;
};
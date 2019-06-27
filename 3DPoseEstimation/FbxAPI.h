#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <QtGui/qquaternion.h>
#include <QtGui/qvector3d.h>
#include <QtGui/qvector4d.h>
#include <QtGui/qmatrix4x4.h>
#include <fbxsdk.h>
#include <json/json.h>

using namespace std;

class FbxAPI {

private:
	FbxManager* gSdkManager = NULL;
	FbxScene* gScene = NULL;
	FbxAnimStack* gAnimStack = NULL;
	FbxAnimLayer* gAnimLayer = NULL;
	FbxNode* gRootNode = NULL;
	FbxNode* gNodeBip001 = NULL;		//14 position translate only
	FbxNode* gNodePelvis = NULL;
	FbxNode* gNodeSpine = NULL;			//14 -> 15 (-1.836,-1.591,33.765) -> (-1.836,-1.585,40.931)		(0,0.006,7.166)
	FbxNode* gNodeL_Thigh = NULL;		//11 -> 12 (0.921,-1.599,30.595) -> (0.921,-1.599,44.376)		(0,0,1)
	FbxNode* gNodeSpine1 = NULL;		//15 -> 1 (-1.836,-1.585,40.931) -> (-1.836,-1.583,48.097)		(0,0.002,7.166)
	FbxNode* gNodeR_Thigh = NULL;		//8	-> 9 (-4.592,-1.599,30.595) -> (-4.592,-1.599,44.376)		(0,0,1)
	FbxNode* gNodeNeck = NULL;			//1 
	FbxNode* gNodeL_Calf = NULL;		//12 -> 13 (0.921,-1.599,44.376) -> (0.921,-1.599,58.158)		(0,0,1)
	FbxNode* gNodeL_Foot = NULL;		//13 -> 20 (0.921,-1.599,58.158) -> (0.921,-5.678,61.327)		(0,-4.079,3.169)
	FbxNode* gNodeHead = NULL;			//1 -> 16 (-1.836,-1.583,48.097) -> (-1.836,-1.583,50.164)		(0,0,1)
	FbxNode* gNodeL_Clavicle = NULL;	//1 -> 5 (-0.871,-1.585,48.097) -> (-0.871,-1.585,51.68)		(0,0,1)
	FbxNode* gNodeR_Clavicle = NULL;	//1 -> 2 (-2.8,-1.585,48.097) -> (-2.8,-1.585,51.68)			(0,0,1)
	FbxNode* gNodeL_UpperArm = NULL;	//5 -> 6 (-0.871,-1.585,51.68) -> (-0.871,-1.585,59.949)		(0,0,1)
	FbxNode* gNodeL_Forearm = NULL;		//6 -> 7 (-0.871,-1.585,59.949) -> (-0.871,-1.585,68.218)		(0,0,1)
	FbxNode* gNodeL_Hand = NULL;		//7 -> 18 X
	FbxNode* gNodeR_UpperArm = NULL;	//2 -> 3														(0,0,1)
	FbxNode* gNodeR_Forearm = NULL;		//3 -> 4														(0,0,1)
	FbxNode* gNodeR_Hand = NULL;		//4 -> 17 X
	FbxNode* gNodeR_Calf = NULL;		//9 -> 10														(0,0,1)
	FbxNode* gNodeR_Foot = NULL;		//10 -> 19 (-4.592,1.139,57.883) -> (-4.592,-2.229,61.8)		(0,-3.368,3.917)
	vector<vector<QVector3D>> gPosition;
	//记录当前处理帧
	int gFrame;
	//记录默认输入FBX文件位置
	const char * inputFBX;

	//rotation(0,0,0) bone vector
	QVector3D gVecSpine;
	QVector3D gVecL_Thigh;
	QVector3D gVecSpine1;
	QVector3D gVecR_Thigh;
	QVector3D gVecL_Calf;
	QVector3D gVecL_Foot;
	QVector3D gVecHead;
	QVector3D gVecL_Clavicle;
	QVector3D gVecR_Clavicle;
	QVector3D gVecL_UpperArm;
	QVector3D gVecL_Forearm;
	QVector3D gVecR_UpperArm;
	QVector3D gVecR_Forearm;
	QVector3D gVecR_Calf;
	QVector3D gVecR_Foot;

	//
	QQuaternion gRotationQuaternion;
	//
	QQuaternion gSpineRotate;
	QQuaternion gL_ThighRotate;
	QQuaternion gSpine1Rotate;
	QQuaternion gR_ThighRotate;
	QQuaternion gL_CalfRotate;
	QQuaternion gL_ClavicleRotate;
	QQuaternion gR_ClavicleRotate;
	QQuaternion gL_UpperArmRotate;
	QQuaternion gR_UpperArmRotate;
	QQuaternion gR_CalfRotate;

	//QVector3D gVecSpine(0, 0.006, 7.166);
	//QVector3D gVecL_Thigh(0, 0, 1);
	//QVector3D gVecSpine1(0, 0.002, 7.166);
	//QVector3D gVecR_Thigh(0, 0, 1);
	//QVector3D gVecL_Calf(0, 0, 1);
	//QVector3D gVecL_Foot(0, -4.079, 3.169);
	//QVector3D gVecHead(0, 0, 1);
	//QVector3D gVecL_Clavicle(0, 0, 1);
	//QVector3D gVecR_Clavicle(0, 0, 1);
	//QVector3D gVecL_UpperArm(0, 0, 1);
	//QVector3D gVecL_Forearm(0, 0, 1);
	//QVector3D gVecR_UpperArm(0, 0, 1);
	//QVector3D gVecR_Forearm(0, 0, 1);
	//QVector3D gVecR_Calf(0, 0, 1);
	//QVector3D gVecR_Foot(0, -3.368, 3.917);
	
	//QVector3D gVecSpine(7.167, -0.005, 0);
	//QVector3D gVecL_Thigh(1, 0, 0);
	//QVector3D gVecSpine1(7.166, -0.002, 0);
	//QVector3D gVecR_Thigh(1, 0, 0);
	//QVector3D gVecL_Calf(1, 0, 0);
	//QVector3D gVecL_Foot(3.169, 4.079, 0);
	//QVector3D gVecHead(1, 0, 0);
	//QVector3D gVecL_Clavicle(1, 0, 0);
	//QVector3D gVecR_Clavicle(1, 0, 0);
	//QVector3D gVecL_UpperArm(1, 0, 0);
	//QVector3D gVecL_Forearm(1, 0, 0);
	//QVector3D gVecR_UpperArm(1, 0, 0);
	//QVector3D gVecR_Forearm(1, 0, 0);
	//QVector3D gVecR_Calf(1, 0, 0);
	//QVector3D gVecR_Foot(3.167, 4.079, 0);

	//初始化
	void Initialize(const char* lFilename);
	//读取3D坐标
	bool ReadPosition(const char* lFilename);
	//处理一帧Vnect3D坐标
	void ProcessOneFrameVnect(vector<QVector3D> lPos);
	//处理一帧OpenMMD3D坐标
	void ProcessOneFrameOpenMMD(vector<QVector3D> lPos);
	//以下分别处理每个关节
	void ProcessBip001(QVector3D lPos);
	void ProcessRotation(FbxNode* lNode, QVector3D eulerAngles);
	void ProcessSpine(QVector3D lPos);
	void ProcessL_Thigh(QVector3D lPos);
	void ProcessSpine1(QVector3D lPos);
	void ProcessR_Thigh(QVector3D lPos);
	void ProcessL_Calf(QVector3D lPos);
	void ProcessL_Foot(QVector3D lPos);
	void ProcessHead(QVector3D lPos);
	void ProcessL_Clavicle(QVector3D lPos);
	void ProcessR_Clavicle(QVector3D lPos);
	void ProcessL_UpperArm(QVector3D lPos);
	void ProcessL_Forearm(QVector3D lPos);
	void ProcessR_UpperArm(QVector3D lPos);
	void ProcessR_Forearm(QVector3D lPos);
	void ProcessR_Calf(QVector3D lPos);
	void ProcessR_Foot(QVector3D lPos);
	//统一坐标系,输入为四元数
	void ModifyCoordinate();

public:
	//构造函数，包括3D坐标文件读取，FBXSKD的初始化.
	FbxAPI(const char * lFilename);
	//处理Vnect3D坐标
	void ProcessFrameVnect();
	//处理OpenMMD3D坐标
	void ProcessFrameOpenMMD();
	//导出FBX文件
	void Export(const char* lExportFilename);
	//释放FBXSDK
	void Destory();
};
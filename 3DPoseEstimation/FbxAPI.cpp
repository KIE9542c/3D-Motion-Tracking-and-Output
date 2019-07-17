#include <fbxsdk.h>
#include "Common.h"
#include "FbxAPI.h"
#define _USE_MATH_DEFINES
#include <math.h>

//-----------------------------------------------------------------------
void FbxAPI::Export(const char* lExportFilename) {
	FbxExporter* lExporter = FbxExporter::Create(gSdkManager, "");

	// Initialize the exporter by providing a filename.
	if (lExporter->Initialize(lExportFilename, 0, gSdkManager->GetIOSettings()) == false)
	{
		exit(0);
	}

	// Export the scene.
	lExporter->Export(gScene);

	// Destroy the exporter.
	lExporter->Destroy();
}
//-----------------------------------------------------------------------
void FbxAPI::Initialize(const char* lFilename) {
	// Prepare the FBX SDK.
	InitializeSdkObjects(gSdkManager, gScene, lFilename);

	//Extract the animation stacks using a pointer to an instance of the FbxScene (pScene).
	int numStacks = gScene->GetSrcObjectCount(FbxCriteria::ObjectType(FbxAnimStack::ClassId));

	FbxAnimStack* gAnimStack = FbxAnimStack::Create(gScene, "");

	////Retrieve the nth animation layer from the animation stack.
	gAnimLayer = FbxAnimLayer::Create(gScene, "Base Layer");
	gAnimStack->AddMember(gAnimLayer);

	gRootNode = gScene->GetRootNode();
	gNodeBip001 = gRootNode->GetChild(0);
	gNodePelvis = gNodeBip001->GetChild(1);
	gNodeSpine = gNodePelvis->GetChild(0);
	gNodeL_Thigh = gNodeSpine->GetChild(0);
	gNodeSpine1 = gNodeSpine->GetChild(2);
	gNodeR_Thigh = gNodeSpine->GetChild(1);
	gNodeNeck = gNodeSpine1->GetChild(0);
	gNodeL_Calf = gNodeL_Thigh->GetChild(0);
	gNodeL_Foot = gNodeL_Calf->GetChild(0);
	gNodeHead = gNodeNeck->GetChild(0);
	gNodeL_Clavicle = gNodeNeck->GetChild(1);
	gNodeR_Clavicle = gNodeNeck->GetChild(2);
	gNodeL_UpperArm = gNodeL_Clavicle->GetChild(0);
	gNodeL_Forearm = gNodeL_UpperArm->GetChild(0);
	gNodeL_Hand = gNodeL_Forearm->GetChild(0);
	gNodeR_UpperArm = gNodeR_Clavicle->GetChild(0);
	gNodeR_Forearm = gNodeR_UpperArm->GetChild(0);
	gNodeR_Hand = gNodeR_Forearm->GetChild(0);
	gNodeR_Calf = gNodeR_Thigh->GetChild(0);
	gNodeR_Foot = gNodeR_Calf->GetChild(0);

	gVecSpine_Global = QVector3D(0, 0.005, 7.166);
	gVecSpine_Local = QVector3D(7.166, -0.005, 0);
	gVecL_Thigh = QVector3D(1, 0, 0);
	gVecSpine1 = QVector3D(7.166, -0.002, 0);
	gVecR_Thigh = QVector3D(1, 0, 0);
	gVecL_Calf = QVector3D(1, 0, 0);
	gVecL_Foot = QVector3D(3.17, 4.079, 0);
	gVecHead = QVector3D(1, 0, 0);
	gVecL_Clavicle = QVector3D(1, 0, 0);
	gVecR_Clavicle = QVector3D(1, 0, 0);
	gVecL_UpperArm = QVector3D(1, 0, 0);
	gVecL_Forearm = QVector3D(1, 0, 0);
	gVecR_UpperArm = QVector3D(1, 0, 0);
	gVecR_Forearm = QVector3D(1, 0, 0);
	gVecR_Calf = QVector3D(1, 0, 0);
	gVecR_Foot = QVector3D(3.17, 4.079, 0);

	gFrame = 0;
}
//-----------------------------------------------------------------------
void FbxAPI::Destory() {
	//gPosition.clear();
	DestroySdkObjects(gSdkManager, true);
}
//-----------------------------------------------------------------------
bool FbxAPI::ReadPosition(const char* lFilename) {
	Json::CharReaderBuilder rbuilder;
	rbuilder["collectComments"] = false;
	Json::Value root;
	JSONCPP_STRING errs;

	fstream f;
	f.open(lFilename, ios::in);
	if (!f.is_open()) {
		cout << "Open json file error!" << endl;
		return false;
	}

	bool parse_ok = Json::parseFromStream(rbuilder, f, &root, &errs);
	if (!parse_ok) {
		cout << "Parse json file error!" << endl;
		return false;
	}
	else {
		try {
			//float a = root["bodies"][1]["position"][0].asFloat();
			//cout << a << endl;
			for (int i = 0; i < root["bodies"].size(); i++)
			{
				cout << "Loading frame " << i << endl;
				vector<QVector3D> lFrame;
				vector<float> lPosition;
				for (int n = 0; n < root["bodies"][i]["position"].size(); n++)
				{
					lPosition.push_back(root["bodies"][i]["position"][n].asFloat());
					if ((n + 1) % 3 == 0) {
						lFrame.push_back(QVector3D(lPosition[0], lPosition[1], lPosition[2]));
						lPosition.clear();
					}
				}
				gPosition.push_back(lFrame);
				lFrame.clear();
			}

		}
		catch (const Json::LogicError &ex) {
			cout << "Parse json string error!" << endl;
			return false;
		}
	}
	f.close();
	return true;
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessOneFrameVnect(vector<QVector3D> lPos) {
	ProcessBip001(lPos[14] - gPosition[0][14]);
	ProcessSpine(lPos[15] - lPos[14]);
	ProcessL_Thigh(lPos[12] - lPos[11]);
	ProcessSpine1(lPos[1] - lPos[15]);
	ProcessR_Thigh(lPos[9] - lPos[8]);
	ProcessL_Calf(lPos[13] - lPos[12]);
	ProcessL_Foot(lPos[20] - lPos[13]);
	ProcessHead(lPos[16] - lPos[1]);
	ProcessL_Clavicle(lPos[5] - lPos[1]);
	ProcessR_Clavicle(lPos[2] - lPos[1]);
	ProcessL_UpperArm(lPos[6] - lPos[5]);
	ProcessL_Forearm(lPos[7] - lPos[6]);
	ProcessR_UpperArm(lPos[3] - lPos[2]);
	ProcessR_Forearm(lPos[4] - lPos[3]);
	ProcessR_Calf(lPos[10] - lPos[9]);
	ProcessR_Foot(lPos[19] - lPos[10]);
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessOneFrameOpenMMD(vector<QVector3D> lPos) {
	ProcessBip001(lPos[0] - gPosition[0][0]);
	ProcessSpine(lPos[7] - lPos[0]);
	ProcessL_Thigh(lPos[5] - lPos[4]);
	ProcessSpine1(lPos[8] - lPos[7]);
	ProcessR_Thigh(lPos[2] - lPos[1]);
	ProcessL_Calf(lPos[6] - lPos[5]);
	ProcessHead(lPos[9] - lPos[8]);
	ProcessL_Clavicle(lPos[11] - lPos[8]);
	ProcessR_Clavicle(lPos[14] - lPos[8]);
	ProcessL_UpperArm(lPos[12] - lPos[11]);
	ProcessL_Forearm(lPos[13] - lPos[12]);
	ProcessR_UpperArm(lPos[15] - lPos[14]);
	ProcessR_Forearm(lPos[16] - lPos[15]);
	ProcessR_Calf(lPos[3] - lPos[2]);
	ProcessRotation(gNodeL_Foot, QVector3D(117,7.7,-65));
	ProcessRotation(gNodeR_Foot, QVector3D(-45,-41,-112));
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessBip001(QVector3D lPos) {
	FbxAnimCurve* lCurveX = NULL;
	FbxAnimCurve* lCurveY = NULL;
	FbxAnimCurve* lCurveZ = NULL;
	FbxTime lTime;
	int lKeyIndex = 0;

	lCurveX = gNodeBip001->LclTranslation.GetCurve(gAnimLayer, FBXSDK_CURVENODE_COMPONENT_X, true);

	if (lCurveX)
	{
		lCurveX->KeyModifyBegin();

		lTime.SetFrame(gFrame);
		lKeyIndex = lCurveX->KeyAdd(lTime);
		lCurveX->KeySet(lKeyIndex, lTime, lPos.x(), FbxAnimCurveDef::eInterpolationLinear);

		lCurveX->KeyModifyEnd();
	}

	lCurveY = gNodeBip001->LclTranslation.GetCurve(gAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y, true);

	if (lCurveY)
	{
		lCurveY->KeyModifyBegin();

		lTime.SetFrame(gFrame);
		lKeyIndex = lCurveY->KeyAdd(lTime);
		lCurveY->KeySet(lKeyIndex, lTime, lPos.y(), FbxAnimCurveDef::eInterpolationLinear);

		lCurveY->KeyModifyEnd();
	}

	lCurveZ = gNodeBip001->LclTranslation.GetCurve(gAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z, true);

	if (lCurveZ)
	{
		lCurveZ->KeyModifyBegin();

		lTime.SetFrame(gFrame);
		lKeyIndex = lCurveZ->KeyAdd(lTime);
		lCurveZ->KeySet(lKeyIndex, lTime, lPos.z(), FbxAnimCurveDef::eInterpolationLinear);

		lCurveZ->KeyModifyEnd();
	}
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessRotation(FbxNode* lNode, QVector3D eulerAngles) {
	FbxAnimCurve* lCurveX = NULL;
	FbxAnimCurve* lCurveY = NULL;
	FbxAnimCurve* lCurveZ = NULL;
	FbxTime lTime;
	int lKeyIndex = 0;

	lCurveX = lNode->LclRotation.GetCurve(gAnimLayer, FBXSDK_CURVENODE_COMPONENT_X, true);

	if (lCurveX)
	{
		lCurveX->KeyModifyBegin();

		lTime.SetFrame(gFrame);
		lKeyIndex = lCurveX->KeyAdd(lTime);
		lCurveX->KeySet(lKeyIndex, lTime, eulerAngles.x(), FbxAnimCurveDef::eInterpolationLinear);

		lCurveX->KeyModifyEnd();
	}

	lCurveY = lNode->LclRotation.GetCurve(gAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y, true);

	if (lCurveY)
	{
		lCurveY->KeyModifyBegin();

		lTime.SetFrame(gFrame);
		lKeyIndex = lCurveY->KeyAdd(lTime);
		lCurveY->KeySet(lKeyIndex, lTime, eulerAngles.y(), FbxAnimCurveDef::eInterpolationLinear);

		lCurveY->KeyModifyEnd();
	}

	lCurveZ = lNode->LclRotation.GetCurve(gAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z, true);

	if (lCurveZ)
	{
		lCurveZ->KeyModifyBegin();

		lTime.SetFrame(gFrame);
		lKeyIndex = lCurveZ->KeyAdd(lTime);
		lCurveZ->KeySet(lKeyIndex, lTime, eulerAngles.z(), FbxAnimCurveDef::eInterpolationLinear);

		lCurveZ->KeyModifyEnd();
	}
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessTranslation(FbxNode* lNode, float translateX) {
	FbxAnimCurve* lCurveX = NULL;
	FbxTime lTime;
	int lKeyIndex = 0;

	lCurveX = lNode->LclTranslation.GetCurve(gAnimLayer, FBXSDK_CURVENODE_COMPONENT_X, true);
	if (lCurveX)
	{
		lCurveX->KeyModifyBegin();

		lTime.SetFrame(gFrame);
		lKeyIndex = lCurveX->KeyAdd(lTime);
		lCurveX->KeySet(lKeyIndex, lTime, translateX, FbxAnimCurveDef::eInterpolationLinear);

		lCurveX->KeyModifyEnd();
	}
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessSpine(QVector3D lPos) {
	//计算这一帧的四元数
	float w;
	gSpineRotate = rotateTo(gVecSpine_Local, lPos,w);
	//写入动画曲线
	QVector3D euler = toEulerAngles(gSpineRotate, w);
	ProcessRotation(gNodeSpine, euler);
	ProcessTranslation(gNodeSpine1, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_Thigh(QVector3D lPos) {
	lPos = gSpineRotate.inverted() * lPos;
	float w;
	gL_ThighRotate = rotateTo(gVecL_Thigh, lPos,w);
	QVector3D euler = toEulerAngles(gL_ThighRotate,w);
	ProcessRotation(gNodeL_Thigh, euler);
	ProcessTranslation(gNodeL_Calf, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessSpine1(QVector3D lPos) {
	lPos = gSpineRotate.inverted() * lPos;
	float w;
	gSpine1Rotate = rotateTo(gVecSpine1, lPos,w);
	QVector3D euler = toEulerAngles(gSpine1Rotate, w);
	ProcessRotation(gNodeSpine1, euler);
	ProcessTranslation(gNodeNeck, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_Thigh(QVector3D lPos) {
	lPos = gSpineRotate.inverted() * lPos;
	float w;
	gR_ThighRotate = rotateTo(gVecR_Thigh, lPos,w);
	QVector3D euler = toEulerAngles(gR_ThighRotate, w);
	ProcessRotation(gNodeR_Thigh, euler);
	ProcessTranslation(gNodeR_Calf, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_Calf(QVector3D lPos) {
	lPos = gL_ThighRotate.inverted() * gSpineRotate.inverted() * lPos;
	float w;
	gL_CalfRotate = rotateTo(gVecL_Calf, lPos,w);
	QVector3D euler = toEulerAngles(gL_CalfRotate, w);
	ProcessRotation(gNodeL_Calf, euler);
	ProcessTranslation(gNodeL_Foot, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_Foot(QVector3D lPos) {
	lPos = gL_CalfRotate.inverted() * gL_ThighRotate.inverted() * gSpineRotate.inverted() * lPos;
	float w;
	gL_FootRotate = rotateTo(gVecL_Foot, lPos,w);
	QVector3D euler = toEulerAngles(gL_FootRotate, w);
	ProcessRotation(gNodeL_Foot, euler);
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessHead(QVector3D lPos) {
	lPos = gSpine1Rotate.inverted() * gSpineRotate.inverted() * lPos;
	float w;
	gHeadRotate = rotateTo(gVecHead, lPos,w);
	QVector3D euler = toEulerAngles(gHeadRotate, w);
	ProcessRotation(gNodeHead, euler);
	ProcessTranslation(gNodeHead, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_Clavicle(QVector3D lPos) {
	lPos = gSpine1Rotate.inverted() * gSpineRotate.inverted() * lPos;
	float w;
	gL_ClavicleRotate = rotateTo(gVecL_Clavicle, lPos,w);
	QVector3D euler = toEulerAngles(gL_ClavicleRotate, w);
	ProcessRotation(gNodeL_Clavicle, euler);
	ProcessTranslation(gNodeL_UpperArm, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_Clavicle(QVector3D lPos) {
	lPos = gSpine1Rotate.inverted() * gSpineRotate.inverted() * lPos;
	float w;
	gR_ClavicleRotate = rotateTo(gVecR_Clavicle, lPos,w);
	QVector3D euler = toEulerAngles(gR_ClavicleRotate, w);
	ProcessRotation(gNodeR_Clavicle, euler);
	ProcessTranslation(gNodeR_UpperArm, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_UpperArm(QVector3D lPos) {
	lPos = gL_ClavicleRotate.inverted() * gSpine1Rotate.inverted() * gSpineRotate.inverted() * lPos;
	float w;
	gL_UpperArmRotate = rotateTo(gVecL_UpperArm, lPos,w);
	QVector3D euler = toEulerAngles(gL_UpperArmRotate, w);
	ProcessRotation(gNodeL_UpperArm, euler);
	ProcessTranslation(gNodeL_Forearm, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_Forearm(QVector3D lPos) {
	lPos = gL_UpperArmRotate.inverted() * gL_ClavicleRotate.inverted() * gSpine1Rotate.inverted() * gSpineRotate.inverted() * lPos;
	float w;
	gL_ForearmRotate = rotateTo(gVecL_Forearm, lPos,w);
	QVector3D euler = toEulerAngles(gL_ForearmRotate, w);
	ProcessRotation(gNodeL_Forearm, euler);
	ProcessTranslation(gNodeL_Hand, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_UpperArm(QVector3D lPos) {
	lPos = gR_ClavicleRotate.inverted() * gSpine1Rotate.inverted() * gSpineRotate.inverted() * lPos;
	float w;
	gR_UpperArmRotate = rotateTo(gVecR_UpperArm, lPos,w);
	QVector3D euler = toEulerAngles(gR_UpperArmRotate, w);
	ProcessRotation(gNodeR_UpperArm, euler);
	ProcessTranslation(gNodeR_Forearm, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_Forearm(QVector3D lPos) {
	lPos = gR_UpperArmRotate.inverted() * gR_ClavicleRotate.inverted() * gSpine1Rotate.inverted() * gSpineRotate.inverted() * lPos;
	float w;
	gR_ForearmRotate = rotateTo(gVecR_Forearm, lPos,w);
	QVector3D euler = toEulerAngles(gR_ForearmRotate, w);
	ProcessRotation(gNodeR_Forearm, euler);
	ProcessTranslation(gNodeR_Hand, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_Calf(QVector3D lPos) {
	lPos = gR_ThighRotate.inverted() * gSpineRotate.inverted() * lPos;
	float w;
	gR_CalfRotate = rotateTo(gVecR_Calf, lPos,w);
	QVector3D euler = toEulerAngles(gR_CalfRotate, w);
	ProcessRotation(gNodeR_Calf, euler);
	ProcessTranslation(gNodeR_Foot, lPos.length());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_Foot(QVector3D lPos) {
	lPos = gR_CalfRotate.inverted() * gR_ThighRotate.inverted() * gSpineRotate.inverted() * lPos;
	float w;
	gR_FootRotate = rotateTo(gVecR_Foot, lPos,w);
	QVector3D euler = toEulerAngles(gR_FootRotate, w);
	ProcessRotation(gNodeR_Foot, euler);
}
//-----------------------------------------------------------------------
QQuaternion FbxAPI::rotateTo(QVector3D from, QVector3D to, float& w) {
	from = from.normalized();
	to = to.normalized();
	QVector3D axis = QVector3D::crossProduct(from, to).normalized();
	float cos_val = QVector3D::dotProduct(from, to);
	float theta = acos(cos_val) * 180 / M_PI;
	w = cos(theta * M_PI / 180 / 2);
	QQuaternion res = QQuaternion::fromAxisAndAngle(axis, theta);
	return res;
}
//-----------------------------------------------------------------------
QVector3D FbxAPI::toEulerAngles(QQuaternion xyz, float w) {
	float x = atan2(2 * (w*xyz.x() + xyz.y()*xyz.z()), 1 - 2 * (pow(xyz.x(), 2) + pow(xyz.y(), 2)));
	float y = asin(2 * (w*xyz.y() - xyz.z()*xyz.x()));
	float z = atan2(2 * (w*xyz.z() + xyz.x()*xyz.y()), 1 - 2 * (pow(xyz.y(), 2) + pow(xyz.z(), 2)));
	x = x * 180 / M_PI;
	y = y * 180 / M_PI;
	z = z * 180 / M_PI;
	return QVector3D(x, y, z);
}
//-----------------------------------------------------------------------
void FbxAPI::ModifyCoordinate_Vnect() {
	for (size_t i = 0; i < gPosition.size(); i++)
	{
		gScale = gVecSpine_Global.length() / (gPosition[i][15] - gPosition[i][14]).length();
		for (size_t n = 0; n < gPosition[i].size(); n++)
		{
			//Vnect/OpenMMD坐标 -> 世界坐标
			QVector3D temp = gRotationQuaternion * gPosition[i][n] * gScale;
			//世界坐标 -> 骨骼局部坐标
			gPosition[i][n].setX(temp.z());
			gPosition[i][n].setY(-temp.y());
			gPosition[i][n].setZ(temp.x());
		}
	}
}
//-----------------------------------------------------------------------
void FbxAPI::ModifyCoordinate_OpenMMD() {
	for (size_t i = 0; i < gPosition.size(); i++)
	{
		gScale = gVecSpine_Global.length() / (gPosition[i][7] - gPosition[i][0]).length();
		for (size_t n = 0; n < gPosition[i].size(); n++)
		{
			//Vnect/OpenMMD坐标 -> 世界坐标
			QVector3D temp = gRotationQuaternion * gPosition[i][n] * gScale;
			//世界坐标 -> 骨骼局部坐标
			gPosition[i][n].setX(temp.z());
			gPosition[i][n].setY(-temp.y());
			gPosition[i][n].setZ(temp.x());
		}
	}
}
//-----------------------------------------------------------------------
FbxAPI::FbxAPI(const char * lFilename) {
	if (ReadPosition(lFilename)) {
		modelPath = "./biped_2Spine.FBX";
		Initialize(modelPath);
	}
	else {
		//TODO: 
	}
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessFrameVnect() {

	gRotationQuaternion = QQuaternion::rotationTo(gPosition[0][15] - gPosition[0][14], gVecSpine_Global);

	ModifyCoordinate_Vnect();

	for (; gFrame < gPosition.size(); gFrame++)
	{
		ProcessOneFrameVnect(gPosition[gFrame]);
	}
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessFrameOpenMMD() {

	gRotationQuaternion = QQuaternion::rotationTo(gPosition[0][7] - gPosition[0][0], gVecSpine_Global);

	ModifyCoordinate_OpenMMD();

	for (; gFrame < gPosition.size(); gFrame++)
	{
		ProcessOneFrameOpenMMD(gPosition[gFrame]);
	}
}
//-----------------------------------------------------------------------
void FbxAPI::setModelPath(const char * lModelPath) {
	modelPath = lModelPath;
}
//-----------------------------------------------------------------------
const char * FbxAPI::getModelPath() {
	return modelPath;
}

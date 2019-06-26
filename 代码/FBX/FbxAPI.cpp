#include <fbxsdk.h>
#include "Common.h"
#include "FbxAPI.h"


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
	FBXSDK_printf("%d\n", numStacks);

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



	FBXSDK_printf("%s\n", gNodeSpine1->GetName());

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
					if ((n+1) % 3 == 0) {
						lFrame.push_back(QVector3D(-lPosition[0],-lPosition[1],lPosition[2]));
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
	cout << "Process frame " << gFrame << endl;
	ProcessBip001(lPos[14]);
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
	ProcessBip001(lPos[0]);
	ProcessSpine(lPos[7] - lPos[0]);
	ProcessL_Thigh(lPos[5] - lPos[4]);
	ProcessSpine1(lPos[8] - lPos[7]);
	ProcessR_Thigh(lPos[2] - lPos[1]);
	ProcessL_Calf(lPos[6] - lPos[5]);
	//ProcessL_Foot(lPos[20] - lPos[13]);
	ProcessHead(lPos[9] - lPos[8]);
	ProcessL_Clavicle(lPos[11] - lPos[8]);
	ProcessR_Clavicle(lPos[14] - lPos[8]);
	ProcessL_UpperArm(lPos[11] - lPos[12]);
	ProcessL_Forearm(lPos[13] - lPos[12]);
	ProcessR_UpperArm(lPos[15] - lPos[14]);
	ProcessR_Forearm(lPos[16] - lPos[15]);
	ProcessR_Calf(lPos[3] - lPos[2]);
	//ProcessR_Foot(lPos[19] - lPos[10]);
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
void FbxAPI::ProcessSpine(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecSpine, lPos);
	ProcessRotation(gNodeSpine, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_Thigh(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecL_Thigh, lPos);
	ProcessRotation(gNodeL_Thigh, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessSpine1(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecSpine1, lPos);
	ProcessRotation(gNodeSpine1, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_Thigh(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecR_Thigh, lPos);
	ProcessRotation(gNodeR_Thigh, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_Calf(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecL_Calf, lPos);
	ProcessRotation(gNodeL_Calf, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_Foot(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecL_Foot, lPos);
	ProcessRotation(gNodeL_Foot, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessHead(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecHead, lPos);
	ProcessRotation(gNodeHead, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_Clavicle(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecL_Clavicle, lPos);
	ProcessRotation(gNodeL_Clavicle, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_Clavicle(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecR_Clavicle, lPos);
	ProcessRotation(gNodeR_Clavicle, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_UpperArm(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecL_UpperArm, lPos);
	ProcessRotation(gNodeL_UpperArm, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessL_Forearm(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecL_Forearm, lPos);
	ProcessRotation(gNodeL_Forearm, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_UpperArm(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecR_UpperArm, lPos);
	ProcessRotation(gNodeR_UpperArm, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_Forearm(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecR_Forearm, lPos);
	ProcessRotation(gNodeR_Forearm, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_Calf(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecR_Calf, lPos);
	ProcessRotation(gNodeR_Calf, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessR_Foot(QVector3D lPos) {
	QQuaternion lRotate = QQuaternion::rotationTo(gVecR_Foot, lPos);
	ProcessRotation(gNodeR_Foot, lRotate.toEulerAngles());
}
//-----------------------------------------------------------------------
FbxAPI::FbxAPI(const char * lFilename) {
	if (ReadPosition(lFilename)) {
		//TODO: 设置为相对路径
		inputFBX = "C:\\Users\\9\\Desktop\\biped_2Spine.FBX";

		Initialize(inputFBX);

		QVector3D gVecSpine(0, 0.006, 7.166);
		QVector3D gVecL_Thigh(0, 0, 1);
		QVector3D gVecSpine1(0, 0.002, 7.166);
		QVector3D gVecR_Thigh(0, 0, 1);
		QVector3D gVecL_Calf(0, 0, 1);
		QVector3D gVecL_Foot(0, -4.079, 3.169);
		QVector3D gVecHead(0, 0, 1);
		QVector3D gVecL_Clavicle(0, 0, 1);
		QVector3D gVecR_Clavicle(0, 0, 1);
		QVector3D gVecL_UpperArm(0, 0, 1);
		QVector3D gVecL_Forearm(0, 0, 1);
		QVector3D gVecR_UpperArm(0, 0, 1);
		QVector3D gVecR_Forearm(0, 0, 1);
		QVector3D gVecR_Calf(0, 0, 1);
		QVector3D gVecR_Foot(0, -3.368, 3.917);

	}
	else {
		//TODO: 
	}
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessFrameVnect() {
	for (; gFrame < gPosition.size(); gFrame++)
	{
		ProcessOneFrameVnect(gPosition[gFrame]);
	}
}
//-----------------------------------------------------------------------
void FbxAPI::ProcessFrameOpenMMD() {
	for (; gFrame < gPosition.size(); gFrame++)
	{
		ProcessOneFrameOpenMMD(gPosition[gFrame]);
	}
}


int main(int /*argc*/, char** /*argv*/)
{
	//const char* lFilename = "C:\\Users\\9\\Desktop\\3.FBX";
	const char* inputFBX = "C:\\Users\\9\\Desktop\\biped_2Spine.FBX";

	const char* inputPosition = "C:\\Users\\9\\Desktop\\3d_posititon.json";

	const char* outputFBX = "C:\\Users\\9\\Desktop\\biped05.FBX";
		
	FbxAPI test(inputPosition);
	test.ProcessFrameVnect();
	test.Export(outputFBX);
	test.Destory();

	//Initialize(inputFBX);
	//gFrame = 5;
	//ProcessRotation(gNodeL_Thigh, QVector3D(90, 0, 0));
	//Export(outputFBX);
	//Destory();
	//FbxAnimCurve* lCurve = NULL;
	//FbxTime lTime;
	//int lKeyIndex = 0;

	//lCurve = gNodeL_UpperArm->LclRotation.GetCurve(gAnimLayer, FBXSDK_CURVENODE_COMPONENT_X, true);

	//if (lCurve)
	//{
	//	lCurve->KeyModifyBegin();

	//	lTime.SetSecondDouble(0.0);
	//	lKeyIndex = lCurve->KeyAdd(lTime);
	//	lCurve->KeySet(lKeyIndex, lTime, 0, FbxAnimCurveDef::eInterpolationLinear);

	//	lTime.SetSecondDouble(2.0);
	//	lKeyIndex = lCurve->KeyAdd(lTime);
	//	lCurve->KeySet(lKeyIndex, lTime, 180, FbxAnimCurveDef::eInterpolationLinear);

	//	lCurve->KeyModifyEnd();
	//}

	//const char* lExportFilename = "C:\\Users\\9\\Desktop\\biped03.FBX";
	//Export(lExportFilename);


//	system("pause");
	return 0;
}

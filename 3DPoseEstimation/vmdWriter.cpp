#include "vmdWriter.h"

vmdWriter::vmdWriter(std::string filename, std::string modelname, bool type) {

	fileName = filename;
	keyFrameNumber = 0;
	isopenMMD = type;
	
	//版本
	for (int i = 27; i < 30; i++)
		version[i] = '\0';

	//模型名字
	if (modelname.size() > 20) {
		std::cout << "The model name should be less than 20 bytes!" << std::endl;
		std::string tempName = "Hatsune Miku";
		for (int i = 0; i < 20; i++) {
			if (i < tempName.size())
				modelName[i] = tempName[i];
			else
				modelName[i] = '\0';
		}
	}
	else {
		for (int i = 0; i < 20; i++) {
			if (i < modelname.size())
				modelName[i] = modelname[i];
			else
				modelName[i] = '\0';
		}
	}

	//补间曲线
	for (int i = 0; i < 4; i++) {
		XCurve[i] = 0;
		YCurve[i] = 0;
		ZCurve[i] = 0;
		RCurve[i] = 0;
	}

	//其他骨骼位置
	for (int i = 0; i < 3; i++)
		position[0][i] = 0;

	if (readPosition())
		std::cout << "complete reading json file!" << std::endl;
	else
		std::cout << "fail to read json file!" << std::endl;

	setBoneIndex();

}

bool vmdWriter::readPosition() {
	Json::CharReaderBuilder rbuilder;
	rbuilder["collectComments"] = false;
	Json::Value root;
	JSONCPP_STRING errs;

	std::fstream f;
	f.open(fileName, std::ios::in);
	if (!f.is_open()) {
		std::cout << "fail to open file!" << std::endl;
		return false;
	}

	bool parse_ok = Json::parseFromStream(rbuilder, f, &root, &errs);
	if (!parse_ok) {
		std::cout << " fail to parse json file!" << std::endl;
		return false;
	}
	else {
		try {
			keyFrameNumber = root["bodies"].size() * 10; //十个骨骼点
			std::cout << "keyFrameNumber ; " << keyFrameNumber << std::endl;
			for (int i = 0; i < root["bodies"].size(); i++) {		
				std::cout << "Loading frame " << i << std::endl;
				std::vector<QVector3D> frame;
				std::vector<float> position;
				for (int n = 0; n < root["bodies"][i]["position"].size(); n++) {
					position.push_back(root["bodies"][i]["position"][n].asFloat());
					if ((n + 1) % 3 == 0) {
						frame.push_back(QVector3D(position[0], position[1], position[2]));
						position.clear();
					}
				}
				gPosition.push_back(frame);
				frame.clear();
			}
		}
		catch (const Json::LogicError &ex) {
			std::cout << "Parse json string error!" << std::endl;
			return false;
		}
	}
	f.close();
	return true;
}

bool vmdWriter::isOpenMMD() {
	return isopenMMD;
}

void vmdWriter::setBoneIndex() {
	if (isOpenMMD()) {
		for (int i = 0; i < 17; i++)
			boneIndex[i] = i;
	}
	else {
		boneIndex[0] = 14;
		boneIndex[1] = 8;
		boneIndex[2] = 9;
		boneIndex[3] = 10;
		boneIndex[4] = 11;
		boneIndex[5] = 12;
		boneIndex[6] = 13;
		boneIndex[7] = 15;
		boneIndex[8] = 1;
		boneIndex[9] = 16;
		boneIndex[10] = 0;
		boneIndex[11] = 5;
		boneIndex[12] = 6;
		boneIndex[13] = 7;
		boneIndex[14] = 2;
		boneIndex[15] = 3;
		boneIndex[16] = 4;
	}
}

void vmdWriter::transferCoordinate(){

	//如果输入视频是倒过来的
	if ((gPosition[0][boneIndex[7]].y() - gPosition[0][boneIndex[0]].y()) < 0) {
		for (int i = 0; i < (keyFrameNumber / 10); i++) {
			for (int j = 0; j < 17; j++) {
				gPosition[i][boneIndex[j]].setY(-gPosition[i][boneIndex[j]].y());
			}
		}
	}
	
	QQuaternion rotateToMMD = QQuaternion::rotationTo(gPosition[0][boneIndex[8]] - gPosition[0][boneIndex[0]], QVector3D(0, 1, 0));
	for (int i = 0; i < (keyFrameNumber / 10); i++) {
		for (int j = 0; j < 17; j++) {
			QVector3D temp = rotateToMMD * gPosition[i][boneIndex[j]];
			gPosition[i][boneIndex[j]].setX(temp.x());
			gPosition[i][boneIndex[j]].setY(temp.y());
			gPosition[i][boneIndex[j]].setZ(temp.z());
		}
	}

}

void vmdWriter::processRotaion(int index) {

	//下半身
	QQuaternion lowerBodyInitial = QQuaternion::fromDirection(QVector3D(0, -1, 0), QVector3D(0, 0, 1));
	QVector3D lowerBodyDirection = gPosition[index][boneIndex[0]] - gPosition[index][boneIndex[7]];
	QVector3D lowerBodyYaw = gPosition[index][boneIndex[4]] - gPosition[index][boneIndex[1]];
	QVector3D lowerBodyUp = QVector3D::crossProduct(lowerBodyDirection, lowerBodyYaw).normalized();
	QQuaternion lowerBodyOrientation = QQuaternion::fromDirection(lowerBodyDirection, lowerBodyUp);
	QQuaternion lowerBodyRotation = lowerBodyOrientation * lowerBodyInitial.inverted();
	QQuaternion lowerBodyRotation1 = QQuaternion::fromEulerAngles(QVector3D(0, lowerBodyRotation.toEulerAngles().y(), 0));
	rotation[1][0] = lowerBodyRotation1.x();
	rotation[1][1] = lowerBodyRotation1.y();
	rotation[1][2] = lowerBodyRotation1.z();
	rotation[1][3] = lowerBodyRotation1.scalar();

	//上半身
	QQuaternion upperBodyInitial = QQuaternion::fromDirection(QVector3D(0, 1, 0), QVector3D(0, 0, 1));
	QVector3D upperBodyDirection = gPosition[index][boneIndex[8]] - gPosition[index][boneIndex[7]];
	QVector3D upperBodyYaw = gPosition[index][boneIndex[14]] - gPosition[index][boneIndex[11]];
	QVector3D upperBodyUp = QVector3D::crossProduct(upperBodyDirection, upperBodyYaw).normalized();
	QQuaternion upperBodyOrientation = QQuaternion::fromDirection(upperBodyDirection, upperBodyUp);
	QQuaternion upperBodyRotation = upperBodyOrientation * upperBodyInitial.inverted();
	QQuaternion upperBodyRotation1 = QQuaternion::fromEulerAngles(QVector3D(0, upperBodyRotation.toEulerAngles().y(), upperBodyRotation.toEulerAngles().z()));
	rotation[2][0] = upperBodyRotation1.x(); 
	rotation[2][1] = upperBodyRotation1.y();
	rotation[2][2] = upperBodyRotation1.z();
	rotation[2][3] = upperBodyRotation1.scalar();

	//首
	QQuaternion neckInitial = QQuaternion::fromDirection(QVector3D(0, -1, 0), QVector3D(0, 0, -1));
	QVector3D neckDirection = gPosition[index][boneIndex[9]] - gPosition[index][boneIndex[8]];
	QVector3D neckYaw = gPosition[index][boneIndex[14]] - gPosition[index][boneIndex[11]];
	QVector3D neckUp = QVector3D::crossProduct(neckYaw, neckDirection).normalized();
	QQuaternion neckOrientation = QQuaternion::fromDirection(neckUp, neckDirection);
	QQuaternion neckRotation = neckOrientation * neckInitial.inverted();
	neckRotation = upperBodyRotation.inverted() * neckRotation;
	QQuaternion neckRotation1 = QQuaternion::fromEulerAngles(QVector3D(0, neckRotation.toEulerAngles().y() - (isopenMMD ? 35.0 : 0.0), neckRotation.toEulerAngles().z() - (isopenMMD ? 12.0 : 0.0)));
	rotation[3][0] = neckRotation1.x();
	rotation[3][1] = neckRotation1.y();
	rotation[3][2] = neckRotation1.z();
	rotation[3][3] = neckRotation1.scalar();

	//左腕
	QQuaternion leftArmInitial = QQuaternion::fromDirection(QVector3D(1.73, -1, 0), QVector3D(1, 1.73, 0));
	QVector3D leftArmDirection = gPosition[index][boneIndex[12]] - gPosition[index][boneIndex[11]];
	QVector3D leftArmYaw = gPosition[index][boneIndex[13]] - gPosition[index][boneIndex[12]];
	QVector3D leftArmUp = QVector3D::crossProduct(leftArmDirection, leftArmYaw).normalized();
	QQuaternion leftArmOrientation = QQuaternion::fromDirection(leftArmDirection, leftArmUp);
	QQuaternion leftArmRotation = leftArmOrientation * leftArmInitial.inverted();
	leftArmRotation = upperBodyRotation.inverted() * leftArmRotation;
	rotation[4][0] = leftArmRotation.x();
	rotation[4][1] = leftArmRotation.y();
	rotation[4][2] = leftArmRotation.z();
	rotation[4][3] = leftArmRotation.scalar();

	//左ひじ
	QQuaternion leftElbowInitial = QQuaternion::fromDirection(QVector3D(1.73, -1, 0), QVector3D(1, 1.73, 0));
	QVector3D leftElbowDirection = gPosition[index][boneIndex[13]] - gPosition[index][boneIndex[12]];
	QVector3D leftElbowYaw = gPosition[index][boneIndex[12]] - gPosition[index][boneIndex[11]];
	QVector3D leftElbowUp = QVector3D::crossProduct(leftElbowYaw, leftElbowDirection).normalized();
	QQuaternion leftElbowOrientation = QQuaternion::fromDirection(leftElbowDirection, leftElbowUp);
	QQuaternion leftElbowRotation = leftElbowOrientation * leftElbowInitial.inverted();
	leftElbowRotation = leftArmRotation.inverted() * upperBodyRotation.inverted() * leftElbowRotation;
	rotation[5][0] = leftElbowRotation.x();
	rotation[5][1] = leftElbowRotation.y();
	rotation[5][2] = leftElbowRotation.z();
	rotation[5][3] = leftElbowRotation.scalar();

	//右腕
	QQuaternion rightArmInitial = QQuaternion::fromDirection(QVector3D(-1.73, -1, 0), QVector3D(1, -1.73, 0));
	QVector3D rightArmDirection = gPosition[index][boneIndex[15]] - gPosition[index][boneIndex[14]];
	QVector3D rightArmYaw = gPosition[index][boneIndex[16]] - gPosition[index][boneIndex[15]];
	QVector3D rightArmUp = QVector3D::crossProduct(rightArmDirection, rightArmYaw).normalized();
	QQuaternion rightArmOrientation = QQuaternion::fromDirection(rightArmDirection, rightArmUp);
	QQuaternion rightArmRotation = rightArmOrientation * rightArmInitial.inverted();
	rightArmRotation = upperBodyRotation.inverted() * rightArmRotation;
	rotation[6][0] = rightArmRotation.x();
	rotation[6][1] = rightArmRotation.y();
	rotation[6][2] = rightArmRotation.z();
	rotation[6][3] = rightArmRotation.scalar();

	//右ひじ
	QQuaternion rightElbowInitial = QQuaternion::fromDirection(QVector3D(-1.73, -1, 0), QVector3D(1, -1.73, 0));
	QVector3D rightElbowDirection = gPosition[index][boneIndex[16]] - gPosition[index][boneIndex[15]];
	QVector3D rightElbowYaw = gPosition[index][boneIndex[15]] - gPosition[index][boneIndex[14]];
	QVector3D rightElbowUp = QVector3D::crossProduct(rightElbowYaw, rightElbowDirection).normalized();
	QQuaternion rightElbowOrientation = QQuaternion::fromDirection(rightElbowDirection, rightElbowUp);
	QQuaternion rightElbowRotation = rightElbowOrientation * rightElbowInitial.inverted();
	rightElbowRotation = rightArmRotation.inverted() * upperBodyRotation.inverted() * rightElbowRotation;
	rotation[7][0] = rightElbowRotation.x();
	rotation[7][1] = rightElbowRotation.y();
	rotation[7][2] = rightElbowRotation.z();
	rotation[7][3] = rightElbowRotation.scalar();

}

void vmdWriter::processPosition(int index) {
	//to do


}

void vmdWriter::writeFile(std::string filePath) {

	
	transferCoordinate();

	//骨骼名字
	char boneName[10][15] = {
	//{ 0x83, 0x4F, 0x83, 0x8B, 0x81, 0x5B, 0x83, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //グルーブ
	{ 0x83, 0x5A, 0x83, 0x93, 0x83, 0x5E, 0x81, 0x5B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //センター
	{ 0x89, 0xBA, 0x94, 0xBC, 0x90, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //下半身
	{ 0x8F, 0xE3, 0x94, 0xBC, 0x90, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //上半身
	{ 0x8E, 0xF1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //首
	//{ 0x93, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //頭
	//{ 0x8D, 0xB6, 0x8C, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //左肩
	{ 0x8D, 0xB6, 0x98, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //左腕
	{ 0x8D, 0xB6, 0x82, 0xD0, 0x82, 0xB6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //左ひじ
	//{ 0x89, 0x45, 0x8C, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //右肩
	{ 0x89, 0x45, 0x98, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //右腕
	{ 0x89, 0x45, 0x82, 0xD0, 0x82, 0xB6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //右ひじ
	//{ 0x8D, 0xB6, 0x91, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //左足
	{ 0x8D, 0xB6, 0x91, 0xAB, 0x82, 0x68, 0x82, 0x6A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //左足ＩＫ
	//{ 0x89, 0x45, 0x91, 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  //右足
	{ 0x89, 0x45, 0x91, 0xAB, 0x82, 0x68, 0x82, 0x6A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }   //右足ＩＫ
	};

	//写头部
	std::fstream file;
	file.open(filePath, std::ios::out | std::ios::binary);
	file.write(version, 30);
	file.write(modelName, 20);
	file.write((char*)&keyFrameNumber, sizeof(uint32_t));

	//写骨骼关键帧记录
	for (uint32_t frame = 0; frame < (keyFrameNumber / 10); frame++) {
		//to do
		memset(rotation, 0, sizeof(rotation));
		memset(position, 0, sizeof(position));
		processRotaion(frame);
		processPosition(frame);
		for (int i = 0; i < 10; i++) {
			file.write(boneName[i], 15);
			file.write((char*)&frame, sizeof(uint32_t));
			switch (i)
			{
			case 0:
				file.write((char*)position[1], sizeof(float) * 3);
				break;
			case 8:
				file.write((char*)position[2], sizeof(float) * 3);
				break;
			case 9:
				file.write((char*)position[3], sizeof(float) * 3);
				break;
			default:
				file.write((char*)position[0], sizeof(float) * 3);
				break;
			}
			file.write((char*)rotation[i], sizeof(float) * 4);
			file.write((char*)XCurve, sizeof(uint32_t) * 4);
			file.write((char*)YCurve, sizeof(uint32_t) * 4);
			file.write((char*)ZCurve, sizeof(uint32_t) * 4);
			file.write((char*)RCurve, sizeof(uint32_t) * 4);
		}
	}
	file.close();
}

void vmdWriter::test() {
	std::fstream file("position.txt", std::ios::out);
	for (int i = 0; i < (keyFrameNumber / 10); i++) {
		//file << "frame: " << i;
		file /*<< "  position[0]: "*/ << gPosition[i][boneIndex[8]].x() << "," << gPosition[i][boneIndex[8]].y() << "," << gPosition[i][boneIndex[8]].z() << std::endl;
			/*<< "  position[1]: " << gPosition[i][1].x() << ", " << gPosition[i][1].y() << ", " << gPosition[i][1].z() << ", "
			<< "  position[4]: " << gPosition[i][4].x() << ", " << gPosition[i][4].y() << ", " << gPosition[i][4].z() << ", "
			<< "  position[3]: " << gPosition[i][3].x() << ", " << gPosition[i][3].y() << ", " << gPosition[i][3].z() << ", "
			<< "  position[6]: " << gPosition[i][6].x() << ", " << gPosition[i][6].y() << ", " << gPosition[i][6].z() << ", "
			<< "  position[7]: " << gPosition[i][7].x() << ", " << gPosition[i][7].y() << ", " << gPosition[i][7].z() << ", "
			<< "  position[8]: " << gPosition[i][8].x() << ", " << gPosition[i][8].y() << ", " << gPosition[i][8].z() << ", "
			<< std::endl;*/
	}
	file.close();
}
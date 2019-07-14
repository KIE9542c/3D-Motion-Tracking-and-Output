#include "MotionContrastor.h"

bool MotionContrastor::getDistance(int Bones[])
{
	length1 = gPosition1.size();
	length2 = gPosition2.size();
	distance=vector<vector<double> >(length1, vector<double>(length2, 0));
	for (int i = 0; i < length1; i++) {
		for (int j = 0; j < length2; j++) {
			for (int k = 0; k < boneSize; k++) {
				int s = Bones[k];
				double x1 = gPosition1[i][s].x();
				double x2 = gPosition2[j][s].x();
				distance[i][j] += (x1 - x2)*(x1 - x2);

				double y1 = gPosition1[i][s].y();
				double y2 = gPosition2[j][s].y();
				distance[i][j] += (y1 - y2)*(y1 - y2);

				double z1 = gPosition1[i][s].z();
				double z2 = gPosition2[j][s].z();
				distance[i][j] += (z1 - z2)*(z1 - z2);
			}
			distance[i][j] = sqrt(distance[i][j]);
		}
	}
	return true;
}



bool MotionContrastor::contrast()
{
	dp= vector<vector<double> >(length1, vector<double>(length2, 0));
	pr= vector<vector<pointOritation> >(length1, vector<pointOritation>(length2));
	
	dp[0][0] = distance[0][0] * 2;

	//计算最下一行
	for (int j = 1; j < length2; j++) {
		dp[0][j] = dp[0][j - 1] + distance[0][j];
		pr[0][j].frontI = 0;
		pr[0][j].frontJ = j - 1;
	}
	//计算最左一列
	for (int i = 1; i < length1; i++) {
		dp[i][0] = dp[i - 1][0] + distance[i][0];
		pr[i][0].frontI = i - 1;
		pr[i][0].frontJ = 0;
	}

	for (int i = 1; i < length1; i++) {
		for (int j = 1; j < length2; j++) {

			//计算左、下、左下（斜）3个方向过来的距离
			double left = dp[i][j - 1] + distance[i][j];
			double under = dp[i - 1][j] + distance[i][j];
			double incline = dp[i - 1][j - 1] + distance[i][j] * 2;

			//比较出3个中最小的
			//先假设从左边过来
			dp[i][j] = left;
			pr[i][j].frontI = i;
			pr[i][j].frontJ = j - 1;
			//比较下边
			if (dp[i][j] > under) {
				dp[i][j] = under;
				pr[i][j].frontI = i - 1;
				pr[i][j].frontJ = j;
			}
			//比较左下
			if (dp[i][j] > incline) {
				dp[i][j] = incline;
				pr[i][j].frontI = i - 1;
				pr[i][j].frontJ = j - 1;
			}

		}
	}
	contrastPoint = dp[length1 - 1][length2 - 1]*1.0/length1;
	contrastPoint /= unit;
	contrastPoint = 100 - 5 * contrastPoint;
	match = vector<vector<int> >(length1);
	int i = length1 - 1;
	int j = length2 - 1;
	while (i || j) {
		match[i].push_back(j);
		int tempI = pr[i][j].frontI;
		int tempJ = pr[i][j].frontJ;
		i = tempI;
		j = tempJ;
	}
	match[0].push_back(0);
	for (int i = 0; i < match.size(); i++) {
		sort(match[i].begin(), match[i].end());
	}
	return true;
}

bool MotionContrastor::readPosition(const char * File, vector<vector<QVector3D>>& gPosition)
{
	Json::CharReaderBuilder rbuilder;
	rbuilder["collectComments"] = false;
	Json::Value root;
	JSONCPP_STRING errs;  

	fstream f;
	f.open(File, ios::in);
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
				vector<double> lPosition;
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

bool MotionContrastor::normalizeVnect()
{
	//骨骼长度标准化
	double lenBody0=0,lenBody1 = 0, lenBody2 = 0, lenBody3 = 0, lenBody4 = 0,lenBody5=0;
	double lenUpperArm_L = 0, lenForeArm_L = 0;
	double lenUpperArm_R = 0, lenForeArm_R = 0;
	double lenThigh_L = 0, lenCalf_L = 0;
	double lenThigh_R = 0, lenCalf_R = 0;
	for (int i = 0; i < gPosition1.size(); i++) {
		//身体
		lenBody0 += gPosition1[i][14].distanceToPoint(gPosition1[i][15]);
		lenBody1 += gPosition1[i][15].distanceToPoint(gPosition1[i][2]);
		lenBody2 += gPosition1[i][15].distanceToPoint(gPosition1[i][5]);
		lenBody3 += gPosition1[i][15].distanceToPoint(gPosition1[i][8]);
		lenBody4 += gPosition1[i][15].distanceToPoint(gPosition1[i][11]);
		lenBody5 += gPosition1[i][15].distanceToPoint(gPosition1[i][14]);
		//左臂
		lenUpperArm_L += gPosition1[i][2].distanceToPoint(gPosition1[i][3]);
        lenForeArm_L += gPosition1[i][3].distanceToPoint(gPosition1[i][4]);
		//右臂
		lenUpperArm_R += gPosition1[i][5].distanceToPoint(gPosition1[i][6]);
		lenForeArm_R += gPosition1[i][6].distanceToPoint(gPosition1[i][7]);
		//左腿
		lenThigh_L += gPosition1[i][8].distanceToPoint(gPosition1[i][9]);
		lenCalf_L += gPosition1[i][9].distanceToPoint(gPosition1[i][10]);
		//右腿
		lenThigh_R += gPosition1[i][11].distanceToPoint(gPosition1[i][12]);
		lenCalf_R += gPosition1[i][12].distanceToPoint(gPosition1[i][13]);
	}
	int cnt = gPosition1.size();
	lenBody0 /= cnt;
	lenBody1 /= cnt;
	lenBody2 /= cnt;
	lenBody3 /= cnt;
	lenBody4 /= cnt;
	lenBody5 /= cnt;
	lenCalf_L /= cnt;
	lenCalf_R /= cnt;
	lenForeArm_L /= cnt;
	lenForeArm_R /= cnt;
	lenThigh_L /= cnt;
	lenThigh_R /= cnt;
	lenUpperArm_L /= cnt;
	lenUpperArm_R /= cnt;
	unit = lenBody5;
	for (int i = 0; i < gPosition1.size(); i++) {
		QVector3D dirBody0 = gPosition1[i][15] - gPosition1[i][14];
		QVector3D dirBody1 = gPosition1[i][2] - gPosition1[i][15];
		QVector3D dirBody2 = gPosition1[i][5] - gPosition1[i][15];
		QVector3D dirBody3 = gPosition1[i][8] - gPosition1[i][15];
		QVector3D dirBody4 = gPosition1[i][11] - gPosition1[i][15];
		QVector3D dirUpperArm_L = gPosition1[i][3] - gPosition1[i][2];
		QVector3D dirFroeArm_L = gPosition1[i][4] - gPosition1[i][3];
		QVector3D dirUpperArm_R = gPosition1[i][6] - gPosition1[i][5];
		QVector3D dirForeArm_R = gPosition1[i][7] - gPosition1[i][6];
		QVector3D dirThigh_L = gPosition1[i][9] - gPosition1[i][8];
		QVector3D dirCalf_L = gPosition1[i][10] - gPosition1[i][9];
		QVector3D dirThigh_R = gPosition1[i][12] - gPosition1[i][11];
		QVector3D dirCalf_R = gPosition1[i][13] - gPosition1[i][12];
		//身体
		gPosition1[i][15] = gPosition1[i][14] + lenBody0 * dirBody0.normalized();
		gPosition1[i][2] = gPosition1[i][15] + lenBody1 * dirBody1.normalized();
		gPosition1[i][5] = gPosition1[i][15] + lenBody2 * dirBody2.normalized();
		gPosition1[i][8] = gPosition1[i][15] + lenBody3 * dirBody3.normalized();
		gPosition1[i][11] = gPosition1[i][15] + lenBody4 * dirBody4.normalized();

		//左臂
		gPosition1[i][3] = gPosition1[i][2] + lenUpperArm_L * dirUpperArm_L.normalized();
		gPosition1[i][4] = gPosition1[i][3] + lenForeArm_L * dirFroeArm_L.normalized();
		
		//右臂
		gPosition1[i][6] = gPosition1[i][5] + lenUpperArm_R * dirUpperArm_R.normalized();
		gPosition1[i][7] = gPosition1[i][6] + lenForeArm_R * dirForeArm_R.normalized();
		
		//左腿
		gPosition1[i][9] = gPosition1[i][8] + lenThigh_L * dirThigh_L.normalized();
		gPosition1[i][10] = gPosition1[i][9] + lenCalf_L * dirCalf_L.normalized();
		
		//右腿
		gPosition1[i][12] = gPosition1[i][11] + lenThigh_R * dirThigh_R.normalized();
		gPosition1[i][13] = gPosition1[i][12] + lenCalf_R * dirCalf_R.normalized();
	}
	/*动作序列2*/
	//序列2平移向量，为了将空间曲线重叠
	QVector3D dirMove = gPosition1[0][14] - gPosition2[0][14];
	for (int i = 0; i < gPosition2.size(); i++) {
		QVector3D dirBody0_2 = gPosition2[i][15] - gPosition2[i][14];
		QVector3D dirBody1_2 = gPosition2[i][2] - gPosition2[i][15];
		QVector3D dirBody2_2 = gPosition2[i][5] - gPosition2[i][15];
		QVector3D dirBody3_2 = gPosition2[i][8] - gPosition2[i][15];
		QVector3D dirBody4_2 = gPosition2[i][11] - gPosition2[i][15];
		QVector3D dirUpperArm_L_2 = gPosition2[i][3] - gPosition2[i][2];
		QVector3D dirFroeArm_L_2 = gPosition2[i][4] - gPosition2[i][3];
		QVector3D dirUpperArm_R_2 = gPosition2[i][6] - gPosition2[i][5];
		QVector3D dirForeArm_R_2 = gPosition2[i][7] - gPosition2[i][6];
		QVector3D dirThigh_L_2 = gPosition2[i][9] - gPosition2[i][8];
		QVector3D dirCalf_L_2 = gPosition2[i][10] - gPosition2[i][9];
		QVector3D dirThigh_R_2 = gPosition2[i][12] - gPosition2[i][11];
		QVector3D dirCalf_R_2 = gPosition2[i][13] - gPosition2[i][12];

		//平移中心关键点
		gPosition2[i][14] = gPosition2[i][14] + dirMove;
		int otherBone[] = { 0,16,1,17,18,19,20 };
		for (int j = 0; j < sizeof(otherBone) / sizeof(int); j++) {
			int k = otherBone[j];
			gPosition2[i][k] = gPosition2[i][k] + dirMove;
		}
		//身体
		gPosition2[i][15] = gPosition2[i][14] + lenBody0 * dirBody0_2.normalized();
		gPosition2[i][2] = gPosition2[i][15] + lenBody1 * dirBody1_2.normalized();
		gPosition2[i][5] = gPosition2[i][15] + lenBody2 * dirBody2_2.normalized();
		gPosition2[i][8] = gPosition2[i][15] + lenBody3 * dirBody3_2.normalized();
		gPosition2[i][11] = gPosition2[i][15] + lenBody4 * dirBody4_2.normalized();

		//左臂
		gPosition2[i][3] = gPosition2[i][2] + lenUpperArm_L * dirUpperArm_L_2.normalized();
		gPosition2[i][4] = gPosition2[i][3] + lenForeArm_L * dirFroeArm_L_2.normalized();

		//右臂
		gPosition2[i][6] = gPosition2[i][5] + lenUpperArm_R * dirUpperArm_R_2.normalized();
		gPosition2[i][7] = gPosition2[i][6] + lenForeArm_R * dirForeArm_R_2.normalized();

		//左腿
		gPosition2[i][9] = gPosition2[i][8] + lenThigh_L * dirThigh_L_2.normalized();
		gPosition2[i][10] = gPosition2[i][9] + lenCalf_L * dirCalf_L_2.normalized();

		//右腿
		gPosition2[i][12] = gPosition2[i][11] + lenThigh_R * dirThigh_R_2.normalized();
		gPosition2[i][13] = gPosition2[i][12] + lenCalf_R * dirCalf_R_2.normalized();
	}
	return true;
}

bool MotionContrastor::normalizeOpenMMD()
{
	//骨骼长度标准化
	double lenBody1 = 0, lenBody2 = 0, lenBody3 = 0, lenBody4 = 0,lenBody5=0,lenBody6=0;
	double lenUpperArm_L = 0, lenForeArm_L = 0;
	double lenUpperArm_R = 0, lenForeArm_R = 0;
	double lenThigh_L = 0, lenCalf_L = 0;
	double lenThigh_R = 0, lenCalf_R = 0;
	for (int i = 0; i < gPosition1.size(); i++) {
		//身体
		lenBody1 += gPosition1[i][8].distanceToPoint(gPosition1[i][14]);
		lenBody2 += gPosition1[i][8].distanceToPoint(gPosition1[i][11]);
		lenBody3 += gPosition1[i][8].distanceToPoint(gPosition1[i][7]);
		lenBody4 += gPosition1[i][7].distanceToPoint(gPosition1[i][0]);
		lenBody5 += gPosition1[i][0].distanceToPoint(gPosition1[i][1]);
		lenBody6 += gPosition1[i][0].distanceToPoint(gPosition1[i][4]);
		//左臂
		lenUpperArm_L += gPosition1[i][14].distanceToPoint(gPosition1[i][15]);
		lenForeArm_L += gPosition1[i][15].distanceToPoint(gPosition1[i][16]);
		//右臂
		lenUpperArm_R += gPosition1[i][11].distanceToPoint(gPosition1[i][12]);
		lenForeArm_R += gPosition1[i][12].distanceToPoint(gPosition1[i][13]);
		//左腿
		lenThigh_L += gPosition1[i][1].distanceToPoint(gPosition1[i][2]);
		lenCalf_L += gPosition1[i][2].distanceToPoint(gPosition1[i][3]);
		//右腿
		lenThigh_R += gPosition1[i][4].distanceToPoint(gPosition1[i][5]);
		lenCalf_R += gPosition1[i][5].distanceToPoint(gPosition1[i][6]);
	}
	int cnt = gPosition1.size();
	lenBody1 /= cnt;
	lenBody2 /= cnt;
	lenBody3 /= cnt;
	lenBody4 /= cnt;
	lenBody5 /= cnt;
	lenBody6 /= cnt;
	lenCalf_L /= cnt;
	lenCalf_R /= cnt;
	lenForeArm_L /= cnt;
	lenForeArm_R /= cnt;
	lenThigh_L /= cnt;
	lenThigh_R /= cnt;
	lenUpperArm_L /= cnt;
	lenUpperArm_R /= cnt;
	unit = lenBody4;
	for (int i = 0; i < gPosition1.size(); i++) {
		QVector3D dirBody1 = gPosition1[i][14] - gPosition1[i][8];
		QVector3D dirBody2 = gPosition1[i][11] - gPosition1[i][8];
		QVector3D dirBody3 = gPosition1[i][8] - gPosition1[i][7];
		QVector3D dirBody4 = gPosition1[i][0] - gPosition1[i][7];
		QVector3D dirBody5 = gPosition1[i][1] - gPosition1[i][0];
		QVector3D dirBody6 = gPosition1[i][4] - gPosition1[i][0];
		QVector3D dirUpperArm_L = gPosition1[i][15] - gPosition1[i][14];
		QVector3D dirFroeArm_L = gPosition1[i][16] - gPosition1[i][15];
		QVector3D dirUpperArm_R = gPosition1[i][12] - gPosition1[i][11];
		QVector3D dirForeArm_R = gPosition1[i][13] - gPosition1[i][12];
		QVector3D dirThigh_L = gPosition1[i][2] - gPosition1[i][1];
		QVector3D dirCalf_L = gPosition1[i][3] - gPosition1[i][2];
		QVector3D dirThigh_R = gPosition1[i][5] - gPosition1[i][4];
		QVector3D dirCalf_R = gPosition1[i][6] - gPosition1[i][5];
		//身体
		gPosition1[i][8] = gPosition1[i][7] + lenBody3 * dirBody3.normalized();
		gPosition1[i][14] = gPosition1[i][8] + lenBody1 * dirBody1.normalized();
		gPosition1[i][11] = gPosition1[i][8] + lenBody2 * dirBody2.normalized();
		gPosition1[i][0] = gPosition1[i][7] + lenBody4 * dirBody4.normalized();
		gPosition1[i][1] = gPosition1[i][0] + lenBody5 * dirBody5.normalized();
		gPosition1[i][4] = gPosition1[i][0] + lenBody6 * dirBody6.normalized();

		//左臂
		gPosition1[i][15] = gPosition1[i][14] + lenUpperArm_L * dirUpperArm_L.normalized();
		gPosition1[i][16] = gPosition1[i][15] + lenForeArm_L * dirFroeArm_L.normalized();

		//右臂
		gPosition1[i][12] = gPosition1[i][11] + lenUpperArm_R * dirUpperArm_R.normalized();
		gPosition1[i][13] = gPosition1[i][12] + lenForeArm_R * dirForeArm_R.normalized();

		//左腿
		gPosition1[i][2] = gPosition1[i][1] + lenThigh_L * dirThigh_L.normalized();
		gPosition1[i][3] = gPosition1[i][2] + lenCalf_L * dirCalf_L.normalized();

		//右腿
		gPosition1[i][5] = gPosition1[i][4] + lenThigh_R * dirThigh_R.normalized();
		gPosition1[i][6] = gPosition1[i][5] + lenCalf_R * dirCalf_R.normalized();
	}
	/*动作序列2*/
	//序列2平移向量，为了将空间曲线重叠
	QVector3D dirMove = gPosition1[0][7] - gPosition2[0][7];
	for (int i = 0; i < gPosition2.size(); i++) {
		QVector3D dirBody1 = gPosition2[i][14] - gPosition2[i][8];
		QVector3D dirBody2 = gPosition2[i][11] - gPosition2[i][8];
		QVector3D dirBody3 = gPosition2[i][8] - gPosition2[i][7];
		QVector3D dirBody4 = gPosition2[i][0] - gPosition2[i][7];
		QVector3D dirBody5 = gPosition2[i][1] - gPosition2[i][0];
		QVector3D dirBody6 = gPosition2[i][4] - gPosition2[i][0];
		QVector3D dirUpperArm_L = gPosition2[i][15] - gPosition2[i][14];
		QVector3D dirFroeArm_L = gPosition2[i][16] - gPosition2[i][15];
		QVector3D dirUpperArm_R = gPosition2[i][12] - gPosition2[i][11];
		QVector3D dirForeArm_R = gPosition2[i][13] - gPosition2[i][12];
		QVector3D dirThigh_L = gPosition2[i][2] - gPosition2[i][1];
		QVector3D dirCalf_L = gPosition2[i][3] - gPosition2[i][2];
		QVector3D dirThigh_R = gPosition2[i][5] - gPosition2[i][4];
		QVector3D dirCalf_R = gPosition2[i][6] - gPosition2[i][5];

		//平移中心关键点
		gPosition2[i][7] = gPosition2[i][7] + dirMove;
		int otherBone[] = { 9,10};
		for (int j = 0; j < sizeof(otherBone) / sizeof(int); j++) {
			int k = otherBone[j];
			gPosition2[i][k] = gPosition2[i][k] + dirMove;
		}
		//身体
		gPosition2[i][8] = gPosition2[i][7] + lenBody3 * dirBody3.normalized();
		gPosition2[i][14] = gPosition2[i][8] + lenBody1 * dirBody1.normalized();
		gPosition2[i][11] = gPosition2[i][8] + lenBody2 * dirBody2.normalized();
		gPosition2[i][0] = gPosition2[i][7] + lenBody4 * dirBody4.normalized();
		gPosition2[i][1] = gPosition2[i][0] + lenBody5 * dirBody5.normalized();
		gPosition2[i][4] = gPosition2[i][0] + lenBody6 * dirBody6.normalized();

		//左臂
		gPosition2[i][15] = gPosition2[i][14] + lenUpperArm_L * dirUpperArm_L.normalized();
		gPosition2[i][16] = gPosition2[i][15] + lenForeArm_L * dirFroeArm_L.normalized();

		//右臂
		gPosition2[i][12] = gPosition2[i][11] + lenUpperArm_R * dirUpperArm_R.normalized();
		gPosition2[i][13] = gPosition2[i][12] + lenForeArm_R * dirForeArm_R.normalized();

		//左腿
		gPosition2[i][2] = gPosition2[i][1] + lenThigh_L * dirThigh_L.normalized();
		gPosition2[i][3] = gPosition2[i][2] + lenCalf_L * dirCalf_L.normalized();

		//右腿
		gPosition2[i][5] = gPosition2[i][4] + lenThigh_R * dirThigh_R.normalized();
		gPosition2[i][6] = gPosition2[i][5] + lenCalf_R * dirCalf_R.normalized();
	}
	return true;
}

bool MotionContrastor::cut(int Bones[])
{
	double MH = 0.5;
	double ML = 1.5;
	length1 = gPosition1.size();
	length2 = gPosition2.size();
	disFrame1 = vector<double>(length1 - 1,0);
	disFrame2 = vector<double>(length2 - 1,0);
	double ave1 = 0;
	for (int i = 0; i < length1 - 1; i++) {
		for (int j = 0; j < boneSize; j++) {
			int k = Bones[j];
			disFrame1[i] += gPosition1[i][k].distanceToPoint(gPosition1[i + 1][k]);
		}
		ave1 += disFrame1[i];
	}
	ave1 /= length1 - 1;
	int start = 0, end = -1;
	for (int i = 0; i < length1-1; i++) {
		if (disFrame1[i] < MH*ave1)end = i;
		else if (disFrame1[i] > ML*ave1)end = i;
		else break;
	}
	if(start<=end)gPosition1.erase(gPosition1.begin() + start, gPosition1.begin() + end);
	length1 = gPosition1.size();
	start = length1, end = length1 - 1;
	for (int i = length1 - 1 - 1; i >= 0; i--) {
		if (disFrame1[i] < MH*ave1)start = i + 1;
		else break;
	}
	if (start <= end)gPosition1.erase(gPosition1.begin() + start, gPosition1.begin() + end);
	length1 = gPosition1.size();
	double ave2 = 0;
	for (int i = 0; i < length2 - 1; i++) {
		for (int j = 0; j < boneSize; j++) {
			int k = Bones[j];
			disFrame2[i] += gPosition2[i][k].distanceToPoint(gPosition2[i + 1][k]);
		}
		ave2 += disFrame2[i];
	}
	ave2 /= length2 - 1;
	start = 0, end = -1;
	for (int i = 0; i < length2-1; i++) {
		if (disFrame2[i] < MH*ave2)end = i;
		else if (disFrame2[i] > ML*ave2)end = i;
		else break;
	}
	if (start <= end)gPosition2.erase(gPosition2.begin() + start, gPosition2.begin() + end);
	length2 = gPosition2.size();
	start = length2, end = length2 - 1;
	for (int i = length2 - 1 - 1; i >= 0; i--) {
		if (disFrame2[i] < MH*ave2)start = i + 1;
		else break;
	}
	if (start <= end)gPosition2.erase(gPosition2.begin() + start, gPosition2.begin() + end);
	length2 = gPosition2.size();
	return true;
}

bool MotionContrastor::contrastVnect(const char * File1, const char * File2)
{
	readPosition(File1, gPosition1);
	readPosition(File2, gPosition2);
	cut(vnectBones);
	normalizeVnect();
	getDistance(vnectBones);
	contrast();
	similarityVnect();
	return true;
}

bool MotionContrastor::contrastOpenMMD(const char * File1, const char * File2)
{
	readPosition(File1, gPosition1);
	readPosition(File2, gPosition2);
	cut(mmdBones);
	normalizeOpenMMD();
	getDistance(mmdBones);
	contrast();
	similarityOpenMMD();
	return true;
}

double MotionContrastor::getPearson(QVector3D a, QVector3D b)
{
	double aveA = (a.x() + a.y() + a.z()) / 3;
	double aveB = (b.x() + b.y() + b.z()) / 3;
	double pea = 0;
	pea += (a.x() - aveA)*(b.x() - aveB);
	pea += (a.y() - aveA)*(b.y() - aveB);
	pea += (a.z() - aveA)*(b.z() - aveB);
	double r1 = 0;
	r1 += (a.x() - aveA)*(a.x() - aveA);
	r1 += (a.y() - aveA)*(a.y() - aveA);
	r1 += (a.z() - aveA)*(a.z() - aveA);
	double r2 = 0;
	r2 += (b.x() - aveB)*(b.x() - aveB);
	r2 += (b.y() - aveB)*(b.y() - aveB);
	r2 += (b.z() - aveB)*(b.z() - aveB);
	pea /= (sqrt(r1)*sqrt(r2));
	return pea;
}

bool MotionContrastor::similarityVnect()
{
	Pear.clear();
	double p = 0.75;
	for (int i = 0; i < match.size(); i++) {
		vector<vector<int >> temp;
		for (int j = 0; j < match[i].size(); j++) {
			int k = match[i][j];
			vector <int> Frame1;
			QVector3D upperArm_L_1 = gPosition1[i][2] - gPosition1[i][3];
			QVector3D upperArm_L_2 = gPosition2[k][2] - gPosition2[k][3];
			Frame1.push_back(getPearson(upperArm_L_1, upperArm_L_2) > p ? 1 : 0);
			QVector3D foreArm_L_1 = gPosition1[i][3] - gPosition1[i][4];
			QVector3D foreArm_L_2 = gPosition2[k][3] - gPosition2[k][4];
			Frame1.push_back(getPearson(foreArm_L_1, foreArm_L_2) > p ? 1 : 0);

			QVector3D upperArm_R_1 = gPosition1[i][5] - gPosition1[i][6];
			QVector3D upperArm_R_2 = gPosition2[k][5] - gPosition2[k][6];
			Frame1.push_back(getPearson(upperArm_R_1, upperArm_R_2) > p ? 1 : 0);
			QVector3D foreArm_R_1 = gPosition1[i][6] - gPosition1[i][7];
			QVector3D foreArm_R_2 = gPosition2[k][6] - gPosition2[k][7];
			Frame1.push_back(getPearson(foreArm_R_1, foreArm_R_2) > p ? 1 : 0);

			QVector3D thigh_L_1 = gPosition1[i][8] - gPosition1[i][9];
			QVector3D thigh_L_2 = gPosition2[k][8] - gPosition2[k][9];
			Frame1.push_back(getPearson(thigh_L_1, thigh_L_2) > p ? 1 : 0);
			QVector3D calf_L_1 = gPosition1[i][9] - gPosition1[i][10];
			QVector3D calf_L_2 = gPosition2[k][9] - gPosition2[k][10];
			Frame1.push_back(getPearson(calf_L_1, calf_L_2) > p ? 1 : 0);

			QVector3D thigh_R_1 = gPosition1[i][11] - gPosition1[i][12];
			QVector3D thigh_R_2 = gPosition2[k][11] - gPosition2[k][12];
			Frame1.push_back(getPearson(thigh_R_1, thigh_R_2) > p ? 1 : 0);
			QVector3D calf_R_1 = gPosition1[i][12] - gPosition1[i][13];
			QVector3D calf_R_2 = gPosition2[k][12] - gPosition2[k][13];
			Frame1.push_back(getPearson(calf_R_1, calf_R_2) > p ? 1 : 0);
			temp.push_back(Frame1);
			Frame1.clear();
		}
		Pear.push_back(temp);
		temp.clear();
	}
	return true;
}

bool MotionContrastor::similarityOpenMMD()
{
	Pear.clear();
	double p = 0.95;
	for (int i = 0; i < match.size(); i++) {
		vector<vector<int >> temp;
		for (int j = 0; j < match[i].size(); j++) {
			int k = match[i][j];
			vector <int> Frame1;
			QVector3D upperArm_L_1 = gPosition1[i][14] - gPosition1[i][15];
			QVector3D upperArm_L_2 = gPosition2[k][14] - gPosition2[k][15];
			Frame1.push_back(getPearson(upperArm_L_1, upperArm_L_2) > p ? 1 : 0);
			QVector3D foreArm_L_1 = gPosition1[i][15] - gPosition1[i][16];
			QVector3D foreArm_L_2 = gPosition2[k][15] - gPosition2[k][16];
			Frame1.push_back(getPearson(foreArm_L_1, foreArm_L_2) > p ? 1 : 0);

			QVector3D upperArm_R_1 = gPosition1[i][11] - gPosition1[i][12];
			QVector3D upperArm_R_2 = gPosition2[k][11] - gPosition2[k][12];
			Frame1.push_back(getPearson(upperArm_R_1, upperArm_R_2) > p ? 1 : 0);
			QVector3D foreArm_R_1 = gPosition1[i][12] - gPosition1[i][13];
			QVector3D foreArm_R_2 = gPosition2[k][12] - gPosition2[k][13];
			Frame1.push_back(getPearson(foreArm_R_1, foreArm_R_2) > p ? 1 : 0);

			QVector3D thigh_L_1 = gPosition1[i][1] - gPosition1[i][2];
			QVector3D thigh_L_2 = gPosition2[k][1] - gPosition2[k][2];
			Frame1.push_back(getPearson(thigh_L_1, thigh_L_2) > p ? 1 : 0);
			QVector3D calf_L_1 = gPosition1[i][2] - gPosition1[i][3];
			QVector3D calf_L_2 = gPosition2[k][2] - gPosition2[k][3];
			Frame1.push_back(getPearson(calf_L_1, calf_L_2) > p ? 1 : 0);

			QVector3D thigh_R_1 = gPosition1[i][4] - gPosition1[i][5];
			QVector3D thigh_R_2 = gPosition2[k][4] - gPosition2[k][5];
			Frame1.push_back(getPearson(thigh_R_1, thigh_R_2) > p ? 1 : 0);
			QVector3D calf_R_1 = gPosition1[i][5] - gPosition1[i][6];
			QVector3D calf_R_2 = gPosition2[k][5] - gPosition2[k][6];
			Frame1.push_back(getPearson(calf_R_1, calf_R_2) > p ? 1 : 0);
			temp.push_back(Frame1);
			Frame1.clear();
		}
		Pear.push_back(temp);
		temp.clear();
	}
	return true;
}

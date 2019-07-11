#include "videoPosePredictor3D.h"

mVideoPosePredictor3D::mVideoPosePredictor3D(const std::string& model_path, const std::string& prototxt_path) :model_path(model_path), prototxt_path(prototxt_path), predictor(model_path, prototxt_path)
{

}

void mVideoPosePredictor3D::predict(const std::string& video_path, const string& shader_dir, const string& mesh_dir, std::vector<std::vector<float>>& output_postition, const bool& is_relative)
{

	GLFWwindow* window;

	cv::VideoCapture video = cv::VideoCapture(video_path);
	std::vector<float> tmp;
	std::vector<float> tmp3d;
	int frameHeight = (int)video.get(CV_CAP_PROP_FRAME_HEIGHT);
	int frameWidth = (int)video.get(CV_CAP_PROP_FRAME_WIDTH);
	int tH = frameHeight, tW = frameWidth;
	for (int i = 2; i * i <= frameHeight; )
	{
		if (tH % i == 0 && tW % i == 0)
		{
			tH /= i;
			tW /= i;
		}
		else
		{
			++i;
		}
	}

	if ((window = InitWindow(wndWidth, wndHeight)) == nullptr) {
		return;
	}
	SetOpenGLState();
	mShader camShader = mShader(shader_dir + "/v.shader", shader_dir + "/f.shader");
	mShader objShader = mShader(shader_dir + "/v2.shader", shader_dir + "/f2.shader");
	mCamera mcam(wndWidth, wndHeight, tW, tH, &camShader, false);

	glm::mat4 projection = glm::perspective(glm::radians(base_vof), wndWidth * 1.0f / wndHeight, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	mMeshRender meshes(view, projection, &objShader);

	meshes.addMesh(mesh_dir + "/sphere2.ply");
	meshes.addMesh(mesh_dir + "/cylinder2.ply");
	glm::mat4 MVP = projection * view * model;
	if (false == mcam.init()) {
		return;
	}

	clock_t start;

	start = clock();

	if (video.isOpened())
	{
		int current_frame_id = 0;
		int total_frame = (int)video.get(CV_CAP_PROP_FRAME_COUNT);
		cv::Mat frame;
		float scale = resize_ratio(frameWidth, frameHeight, det_width, det_height);
		float resize_height = frameHeight * scale;
		float resize_width = frameWidth * scale;
		int center_point_x = det_width / 2;
		int center_point_y = det_height / 2;
		cv::Rect det_box(center_point_x - resize_width / 2, center_point_y - resize_height / 2, resize_width, resize_height);


		AVFormatContext* fmt_ctx = nullptr;
		avformat_open_input(&fmt_ctx, video_path.c_str(), nullptr, nullptr);//打开一个视频
		avformat_find_stream_info(fmt_ctx, nullptr);//读取视频，然后得到流和码率等信息
		AVStream* stream = fmt_ctx->streams[0];
		double rotation = get_rotation(stream);
		do
		{
			if (!video.read(frame))
			{
				break;
			}

			if (fabs(rotation - 180) < 1.0 || fabs(rotation + 180) < 1.0)
			{
				cv::flip(frame, frame, 0);
			}

			cv::Mat detect_mat(det_height, det_width, CV_8UC3, cv::Scalar(0, 0, 0));
			cv::Mat detect_roi = detect_mat(det_box);
			cv::Mat image_roi = frame.clone();
			cv::resize(image_roi, image_roi, cv::Size(resize_width, resize_height));
			image_roi.copyTo(detect_roi);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			current_frame_id++;
			char c[8];
			int length = sprintf_s(c, "%d", current_frame_id);
			USES_CONVERSION;
			OutputDebugString(A2W(c));
			OutputDebugString(L"\n");
			predictor.predict(detect_mat, tmp, tmp3d, is_relative);
			std::vector<float> vertexs;
			joints_scale_3d(tmp3d, vertexs);
			output_postition.push_back(vertexs);


			glm::mat4 curModel;
			if (isMousePressed && (initX != curX || initY != curY)) {
				float tmpZ2;
				float tmpinitX = ((float)(wndWidth - initX - 1) / (float)wndHeight - 0.5) * 2;
				float tmpinitY = ((float)initY / (float)wndHeight - 0.5) * 2;
				tmpZ2 = 1 - tmpinitX * tmpinitX - tmpinitY * tmpinitY;
				glm::vec3 initVec(1.0);
				if (tmpZ2 < 0) {
					float tLen = sqrt(tmpinitY * tmpinitY + tmpinitX * tmpinitX);
					glm::vec4 from(tmpinitX / tLen, tmpinitY / tLen, 0, 1.0);
					glm::mat4 rmat = glm::rotate(glm::mat4(1.0), 1 - tLen, glm::cross(glm::vec3(tmpinitX, tmpinitY, 0), glm::vec3(0, 0, 1)));

					glm::vec4 tmpm = rmat * from;
					initVec.x = tmpm.x;
					initVec.y = tmpm.y;
					initVec.z = tmpm.z;
				}
				else {
					initVec = glm::normalize(glm::vec3(tmpinitX, tmpinitY, sqrt(tmpZ2)));
				}

				float tmpcurX = ((float)(wndWidth - curX - 1) / (float)wndHeight - 0.5) * 2;
				float tmpcurY = ((float)curY / (float)wndHeight - 0.5) * 2;
				glm::vec3 curVec;
				tmpZ2 = 1 - tmpcurX * tmpcurX - tmpcurY * tmpcurY;
				if (tmpZ2 < 0) {
					float tLen = sqrt(tmpcurY * tmpcurY + tmpcurX * tmpcurX);
					glm::vec4 from(tmpcurX / tLen, tmpcurY / tLen, 0, 1.0);
					glm::mat4 rmat = glm::rotate(glm::mat4(1.0), 1 - tLen, glm::cross(glm::vec3(tmpcurX, tmpcurY, 0), glm::vec3(0, 0, 1)));
					glm::vec4 tmpm = rmat * from;
					curVec.x = tmpm.x;
					curVec.y = tmpm.y;
					curVec.z = tmpm.z;
				}
				else {
					curVec = glm::normalize(glm::vec3(tmpcurX, tmpcurY, sqrt(tmpZ2)));
				}

				rotateMat = glm::rotate(glm::mat4(1.0), glm::acos(glm::dot(initVec, curVec)), glm::cross(curVec, initVec));
				curModel = rotateMat * model;
			}
			else {
				curModel = model;
			}

			cv::resize(frame, frame, cv::Size(wndWidth, wndHeight));
			drawPoint(frame, tmp, det_box);
			sprintf_s(txt_buffer, "%.1f", (1.0 / (-start + clock()) * 1000));
			drawText(frame, "FPS:" + string(txt_buffer));
			start = clock();
			cv::flip(frame, frame, 1);
			mcam.drawFrame(frame);

			meshes.render(vertexs, joint_indics, curModel);

			glfwSwapBuffers(window);
			glfwPollEvents();

		} while (current_frame_id < total_frame && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
		OutputDebugString(L"输出调DD试信息123");
		OutputDebugString(L"\n");
		avformat_close_input(&fmt_ctx);
	}
	video.release();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void mVideoPosePredictor3D::writePositionToJson(const std::string& path, const std::vector<std::vector<float>>& output_postition)
{
	OutputDebugString(L"write json");
	OutputDebugString(L"\n");
	writeToJson(path, output_postition);
	OutputDebugString(L"write finish");
	OutputDebugString(L"\n");
}

void mVideoPosePredictor3D::predict_t(const string& video_path, const string& shader_dir, const string& mesh_dir, std::vector<std::vector<float>> output, const bool& is_relative, const bool& is_show)
{
	HANDLE hThread;
	DWORD dwThreadId;
	param_t* param = new param_t{ &is_relative,&is_show,shader_dir.c_str() ,mesh_dir.c_str() ,video_path.c_str() ,&predictor,&output };

	hThread = CreateThread(NULL	// 默认安全属性
		, NULL		// 默认堆栈大小
		, ThreadProFunc // 线程入口地址
		, param	//传递给线程函数的参数
		, 0		// 指定线程立即运行
		, &dwThreadId	//线程ID号
	);
	WaitForSingleObject(hThread, INFINITE);

}

void mVideoPosePredictor3D::predict_notShow(const std::string& video_path, const string& shader_dir, const string& mesh_dir, std::vector<std::vector<float>>& output_postition, const bool& is_relative)
{
	cv::VideoCapture video = cv::VideoCapture(video_path);
	std::vector<float> tmp;
	std::vector<float> tmp3d;
	int frameHeight = (int)video.get(CV_CAP_PROP_FRAME_HEIGHT);
	int frameWidth = (int)video.get(CV_CAP_PROP_FRAME_WIDTH);
	int tH = frameHeight, tW = frameWidth;
	for (int i = 2; i * i <= frameHeight; )
	{
		if (tH % i == 0 && tW % i == 0)
		{
			tH /= i;
			tW /= i;
		}
		else
		{
			++i;
		}
	}


	clock_t start;

	start = clock();

	if (video.isOpened())
	{
		int current_frame_id = 0;
		int total_frame = (int)video.get(CV_CAP_PROP_FRAME_COUNT);
		cv::Mat frame;
		do
		{
			if (!video.read(frame))
			{
				break;
			}
			current_frame_id++;
			char c[8];
			int length = sprintf_s(c, "%d", current_frame_id);
			USES_CONVERSION;
			OutputDebugString(A2W(c));
			OutputDebugString(L"\n");
			predictor.predict(frame, tmp, tmp3d, is_relative);
			std::vector<float> vertexs;
			joints_scale_3d(tmp3d, vertexs);
			output_postition.push_back(vertexs);

			start = clock();


		} while (current_frame_id);
		OutputDebugString(L"输出调DD试信息123");
		OutputDebugString(L"\n");
	}
}

float mVideoPosePredictor3D::resize_ratio(const float& picture_width, const float& picture_height, const float& default_width, const float& default_height)
{
	float widthRatio = default_width / picture_width;
	float heightRatio = default_height / picture_height;
	float ratio = 0;
	widthRatio < heightRatio ? ratio = widthRatio : ratio = heightRatio;
	return ratio;
}


void joints_scale_3d(const std::vector<float>& joints3d, std::vector<float>& result)
{
	result.clear();
	int scale_size = 1;
	for (int i = 0; i < joint_num; ++i)
	{
		// here I need to normalize them
		//

		result.push_back(scale_size * static_cast<float>(joints3d[i * 3]));
		result.push_back(scale_size * static_cast<float>(joints3d[i * 3 + 1]));
		result.push_back(scale_size * static_cast<float>(joints3d[i * 3 + 2]));

		char c[20];
		int length = sprintf_s(c, "%f", joints3d[i * 3]);
		USES_CONVERSION;
		OutputDebugString(A2W(c));
		length = sprintf_s(c, "%f", joints3d[i * 3 + 1]);
		OutputDebugString(A2W(c));
		length = sprintf_s(c, "%f", joints3d[i * 3 + 2]);
		OutputDebugString(A2W(c));
		OutputDebugString(L"\n");
	}
}

double get_rotation(AVStream* st)
{
	AVDictionaryEntry* rotate_tag = av_dict_get(st->metadata, "rotate", NULL, 0);
	double theta = 0;

	if (rotate_tag && *rotate_tag->value && strcmp(rotate_tag->value, "0")) {
		//char *tail;
		//theta = av_strtod(rotate_tag->value, &tail);
		theta = atof(rotate_tag->value);
		// if (*tail)
			// theta = 0;
	}

	theta -= 360 * floor(theta / 360 + 0.9 / 360);

	return theta;
}

void SetOpenGLState()
{
	// enable depth test and accept fragment if it closer to the camera than the former one
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}


DWORD WINAPI ThreadProFunc(LPVOID lpParam)
{
	caffe::Caffe::set_mode(caffe::Caffe::GPU);
	caffe::Caffe::SetDevice(0);
	param_t* param = (param_t*)lpParam;
	string video_path = string(param->video_path);
	bool is_show = *(param->is_show), is_relative = *(param->is_relative);
	string shader_dir = string(param->shader_dir);
	string mesh_dir = string(param->mesh_dir);
	vector<vector<float>> output_postition = (*param->positions);
	mVNectUtils* predictor = param->predictor;
	GLFWwindow* window;

	cv::VideoCapture video = cv::VideoCapture(video_path);
	std::vector<float> tmp;
	std::vector<float> tmp3d;
	int frameHeight = (int)video.get(CV_CAP_PROP_FRAME_HEIGHT);
	int frameWidth = (int)video.get(CV_CAP_PROP_FRAME_WIDTH);
	int tH = frameHeight, tW = frameWidth;
	for (int i = 2; i * i <= frameHeight; )
	{
		if (tH % i == 0 && tW % i == 0)
		{
			tH /= i;
			tW /= i;
		}
		else
		{
			++i;
		}
	}
	if ((window = InitWindow(frameWidth, frameHeight)) == nullptr && is_show) {
		return -1;
	}
	SetOpenGLState();
	mShader camShader = mShader(shader_dir + "/v.shader", shader_dir + "/f.shader");
	mShader objShader = mShader(shader_dir + "/v2.shader", shader_dir + "/f2.shader");
	mCamera mcam(frameWidth, frameHeight, tW, tH, &camShader, false);

	glm::mat4 projection = glm::perspective(glm::radians(base_vof), frameWidth * 1.0f / frameHeight, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	mMeshRender meshes(view, projection, &objShader);

	meshes.addMesh(mesh_dir + "/sphere2.ply");
	meshes.addMesh(mesh_dir + "/cylinder2.ply");
	glm::mat4 MVP = projection * view * model;
	if (false == mcam.init()) {
		return -1;
	}

	clock_t start;

	start = clock();

	if (video.isOpened())
	{
		int current_frame_id = 0;
		int total_frame = (int)video.get(CV_CAP_PROP_FRAME_COUNT);
		cv::Mat frame;
		do
		{
			if (!video.read(frame))
			{
				break;
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			current_frame_id++;
			char c[8];
			int length = sprintf_s(c, "%d", current_frame_id);
			USES_CONVERSION;
			OutputDebugString(A2W(c));
			OutputDebugString(L"\n");
			predictor->predict(frame, tmp, tmp3d, is_relative);
			std::vector<float> vertexs;
			joints_scale_3d(tmp3d, vertexs);
			output_postition.push_back(vertexs);



			if (is_show)
			{


				glm::mat4 curModel;
				if (isMousePressed && (initX != curX || initY != curY)) {
					float tmpZ2;
					float tmpinitX = ((float)(frameWidth - initX - 1) / (float)frameHeight - 0.5) * 2;
					float tmpinitY = ((float)initY / (float)frameHeight - 0.5) * 2;
					tmpZ2 = 1 - tmpinitX * tmpinitX - tmpinitY * tmpinitY;
					glm::vec3 initVec(1.0);
					if (tmpZ2 < 0) {
						float tLen = sqrt(tmpinitY * tmpinitY + tmpinitX * tmpinitX);
						glm::vec4 from(tmpinitX / tLen, tmpinitY / tLen, 0, 1.0);
						glm::mat4 rmat = glm::rotate(glm::mat4(1.0), 1 - tLen, glm::cross(glm::vec3(tmpinitX, tmpinitY, 0), glm::vec3(0, 0, 1)));

						glm::vec4 tmpm = rmat * from;
						initVec.x = tmpm.x;
						initVec.y = tmpm.y;
						initVec.z = tmpm.z;
					}
					else {
						initVec = glm::normalize(glm::vec3(tmpinitX, tmpinitY, sqrt(tmpZ2)));
					}

					float tmpcurX = ((float)(frameWidth - curX - 1) / (float)frameHeight - 0.5) * 2;
					float tmpcurY = ((float)curY / (float)frameHeight - 0.5) * 2;
					glm::vec3 curVec;
					tmpZ2 = 1 - tmpcurX * tmpcurX - tmpcurY * tmpcurY;
					if (tmpZ2 < 0) {
						float tLen = sqrt(tmpcurY * tmpcurY + tmpcurX * tmpcurX);
						glm::vec4 from(tmpcurX / tLen, tmpcurY / tLen, 0, 1.0);
						glm::mat4 rmat = glm::rotate(glm::mat4(1.0), 1 - tLen, glm::cross(glm::vec3(tmpcurX, tmpcurY, 0), glm::vec3(0, 0, 1)));
						glm::vec4 tmpm = rmat * from;
						curVec.x = tmpm.x;
						curVec.y = tmpm.y;
						curVec.z = tmpm.z;
					}
					else {
						curVec = glm::normalize(glm::vec3(tmpcurX, tmpcurY, sqrt(tmpZ2)));
					}

					rotateMat = glm::rotate(glm::mat4(1.0), glm::acos(glm::dot(initVec, curVec)), glm::cross(curVec, initVec));
					curModel = rotateMat * model;
				}
				else {
					curModel = model;
				}

				drawPoint(frame, tmp);
				sprintf_s(txt_buffer, "%.1f", (1.0 / (-start + clock()) * 1000));
				drawText(frame, "FPS:" + string(txt_buffer));
				start = clock();
				cv::flip(frame, frame, 1);
				mcam.drawFrame(frame);

				meshes.render(vertexs, joint_indics, curModel);

				glfwSwapBuffers(window);
				glfwPollEvents();
			}
		} while (current_frame_id < total_frame && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
		OutputDebugString(L"输出调DD试信息123");
		OutputDebugString(L"\n");
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


GLFWwindow* InitWindow(float wndWidth, float wndHeight)
{
	glfwSetErrorCallback(error_callback);
	if (false == glfwInit()) {
		std::cout << "glfwInit failed!" << std::endl;
		return nullptr;
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);// ? Don't know what's it;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(wndWidth, wndHeight, "3D Pose Estimate", nullptr, nullptr);
	if (!window) {
		std::cout << "Window create failed!" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSwapInterval(0);

	if (!gladLoadGL()) {
		std::cout << "Failed to initialize GLEW\n" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	return window;
}

void drawPoint(cv::Mat& img, const std::vector<float>& pos)
{
	for (int i = 0; i < joint_num; ++i)
	{

		int x = (pos[i * 2 + 0] + 0.5) * img.size().height;
		int y = (pos[i * 2 + 1] + 0.5) * img.size().width;
		for (int j = -2; j < 3; ++j)
		{
			for (int k = -2; k < 3; ++k)
			{
				if (x + j < 0 || x + j >= img.size().height || y + k >= img.size().width || y + k < 0)
				{
					std::cout << "out of range" << std::endl;
					continue;
				}
				// TODO:Here you need to get to know how the oepncv store data and how to 
				//      access the data in the mat.
				img.at<float>(x + j, y + k, 0) = 1;
				//img.at<char>(pos[i][0]+j, pos[i][1]+k, 2) = 1;
			}
		}

	}
}

void drawPoint(cv::Mat& img, const std::vector<float>& pos, cv::Rect r)
{
	for (int i = 0; i < joint_num; ++i)
	{

		int x = (pos[i * 2 + 0] + 0.5) * det_height;
		int y = (pos[i * 2 + 1] + 0.5) * det_width;
		x = 1.0 * (x - r.y) * img.cols / det_width;
		y = 1.0 * (y - r.x) * img.rows / det_height;

		for (int j = -2; j < 3; ++j)
		{
			for (int k = -2; k < 3; ++k)
			{
				if (x + j < 0 || x + j >= img.size().height || y + k >= img.size().width || y + k < 0)
				{
					std::cout << "out of range" << std::endl;
					continue;
				}
				img.at<float>(x + j, y + k, 0) = 1;
			}
		}

	}
}

void drawText(cv::Mat& img, const string& text)
{
	cv::Size txt_size = cv::getTextSize(text, font_face, font_scale, thickness, &text_line);
	cv::Point origin(0, txt_size.height);
	cv::putText(img, text, origin, font_face, font_scale, cv::Scalar(0, 0, 255));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			printf("Pressed left Key!\n");
			initX = curX;
			initY = curY;
			isMousePressed = true;
			break;
		}
	}
	else {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			printf("Release left Key!\n");
			isMousePressed = false;
			model = rotateMat * model;
			//rotateMat = glm::mat4(1.0);
			break;
		}
	}
}

void mouse_move_callback(GLFWwindow* window, double x, double y)
{
	curX = x;
	curY = y;

	if (isMousePressed) {
		std::cout << "cursor is at (" << curX << ", " << curY << ")" << std::endl;
	}
}


void error_callback(int error, const char* description)
{
	printf("glfwERROR: code %d, desc:%s\n", error, description);
}

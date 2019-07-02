#include "AlphaBaseLine.h"

namespace alphaBaseline
{
	AlphaBaseline::AlphaBaseline(const string& yolo_cfg, const string& yolo_weight, const string& alpahaPose_path, const string& baseline_path) :baseline(baseline_path)
	{
		
		if (torch::cuda::is_available()) {
			device_type = torch::kCUDA;
		}
		else {
			device_type = torch::kCPU;
		}

		torch::Device device(device_type);

		net = Darknet(yolo_cfg.c_str(), &device);

		std::map<string, string>* info = net.get_net_info();
		info->operator[]("height") = std::to_string(input_image_size);
		std::cout << "loading weight ..." << std::endl;

		net.load_weights(yolo_weight.c_str());
		std::cout << "yolo weight loaded ..." << std::endl;
		module = torch::jit::load(alpahaPose_path);
		std::cout << "alphaPose weight loaded ..." << std::endl;
		std::cout << alpahaPose_path << std::endl;

		module->to(device);
		net.to(device);
		torch::NoGradGuard no_grad;
		net.eval();

	}

	int AlphaBaseline::predict(const string& video_path, const string& shader_dir, const string& mesh_dir, std::vector<std::vector<float>> position_3d)
	{
		position_3d.clear();

		std::cout << "loading video ..." << std::endl;
		cv::VideoCapture m_cam = cv::VideoCapture(video_path);
		if (!m_cam.isOpened())
		{
			std::cout << "null vedio" << std::endl;
			return -1;
		}
		std::cout << "video loaded ..." << std::endl;
		int frameHeight = (int)m_cam.get(CV_CAP_PROP_FRAME_HEIGHT);
		int frameWidth = (int)m_cam.get(CV_CAP_PROP_FRAME_WIDTH);
		int fps = (int)m_cam.get(CV_CAP_PROP_FPS);
		int numFrames = (int)m_cam.get(CV_CAP_PROP_FRAME_COUNT);
		std::cout << "frameW,frameH,fps,numFrame=" << frameHeight << "," << frameWidth << "," << fps << "," << numFrames << std::endl;

		//init window
		GLFWwindow* window;
		if ((window = InitWindow(frameWidth, frameHeight)) == nullptr) {
			return -1;
		}
		//load shade
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
		mShader camShader(shader_dir+"/v.shader",
			shader_dir+"/f.shader");
		mShader objShader(shader_dir + "/v2.shader",
			shader_dir + "/f2.shader");
		mCamera mcam(frameWidth, frameHeight, tW, tH, &camShader, false);
		if (false == mcam.init()) {
			return -1;
		}

		//load mesh
		glm::mat4 projection = glm::perspective(glm::radians(base_vof), frameWidth * 1.0f / frameHeight, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		glm::mat4 MVP = projection * view * model;
		mMeshRender meshes(view, projection, &objShader);
		meshes.addMesh(mesh_dir+"/sphere2.ply");
		meshes.addMesh(mesh_dir+"/cylinder2.ply");



		//main proc
		std::cout << "start to inference ..." << std::endl;
		int frame_id = 0;
		cv::Mat frame;
		std::vector<float> front_pose;
		clock_t start;

		start = clock();

		do
		{
			if (!m_cam.read(frame)) {
				break;
			}
			
			++frame_id;
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			cv::Mat origin_image = frame, resized_image_yolo;
			cv::cvtColor(origin_image, resized_image_yolo, cv::COLOR_RGB2BGR);
			cv::resize(resized_image_yolo, resized_image_yolo, cv::Size(input_image_size, input_image_size));

			//cv to torch
			cv::Mat img_float_yolo;
			resized_image_yolo.convertTo(img_float_yolo, CV_32F, 1.0 / 255);
			torch::Tensor img_tensor = torch::CPU(torch::kFloat32).tensorFromBlob(img_float_yolo.data, { 1, input_image_size, input_image_size, 3 });
			img_tensor = img_tensor.permute({ 0,3,1,2 });
			torch::Tensor img_var = torch::autograd::make_variable(img_tensor, false).to(device_type);
			//yolo detect
			torch::Tensor output = net.forward(img_var);
			torch::Tensor result = net.write_results(output, 80, 0.5, 0.6);
			std::cout << -start + clock() << std::endl;
		

			//2d pose detect
			if (result.dim() == 1 || result.size(0) == 0)
			{
				cv::flip(origin_image, origin_image, 1);
				mcam.drawFrame(origin_image);
				glfwSwapBuffers(window);
				glfwPollEvents();
				std::cout << "no object found" << std::endl;
			}
			else
			{
				
				int obj_num = result.size(0);


				float w_scale = float(origin_image.cols) / input_image_size;
				float h_scale = float(origin_image.rows) / input_image_size;
				result.select(1, 1).mul_(w_scale);
				result.select(1, 2).mul_(h_scale);
				result.select(1, 3).mul_(w_scale);
				result.select(1, 4).mul_(h_scale);

				auto result_data = result.accessor<float, 2>();


				cv::Mat resized_mat;
				cv::cvtColor(origin_image, origin_image, cv::COLOR_BGR2RGB);


				int max_score_index = 0;
				float max_score = 0;
				for (int i = 0; i < result.size(0); ++i)
				{
					if (result_data[i][5] > max_score)
					{
						max_score = result_data[i][5];
						max_score_index = i;
					}
				}

				//cv::rectangle(origin_image, cv::Point(result_data[max_score_index][1], result_data[max_score_index][2]), cv::Point(result_data[max_score_index][3], result_data[max_score_index][4]), cv::Scalar(0, 0, 255), 1, 1, 0);


				//resize box
				cv::Rect rect(result_data[max_score_index][1], result_data[max_score_index][2],
					result_data[max_score_index][3] - result_data[max_score_index][1] + 1,
					result_data[max_score_index][4] - result_data[max_score_index][2] + 1);
				result_data[max_score_index][1] = std::max(0.0, rect.x - rect.width * 0.3 / 2);
				result_data[max_score_index][2] = std::max(0.0, rect.y - rect.height * 0.3 / 2);
				result_data[max_score_index][3] = std::max(
					std::min(origin_image.cols - 1.0,
						result_data[max_score_index][3] + rect.width * 0.3 / 2),
					result_data[max_score_index][1] + 5.0);
				result_data[max_score_index][4] = std::max(
					std::min(origin_image.rows - 1.0,
						result_data[max_score_index][4] + rect.width * 0.3 / 2),
					result_data[max_score_index][2] + 5.0);


				cv::Rect rect2(result_data[max_score_index][1], result_data[max_score_index][2], result_data[max_score_index][3] - result_data[max_score_index][1] + 1, result_data[max_score_index][4] - result_data[max_score_index][2] + 1);




				//resize image
				float scale = resize_ratio(rect2.width, rect2.height, det_width, det_height);
				float resize_height = rect2.height * scale;
				float resize_width = rect2.width * scale;
				cv::Mat detect_mat(det_height, det_width, CV_8UC3, cv::Scalar(0, 0, 0));
				int center_point_x = detect_mat.cols / 2;
				int center_point_y = detect_mat.rows / 2;
				cv::Rect det_box(center_point_x - resize_width / 2, center_point_y - resize_height / 2, resize_width, resize_height);
				cv::Mat detect_roi = detect_mat(det_box);
				cv::Mat image_roi = origin_image(rect2);
				cv::resize(image_roi, image_roi, cv::Size(resize_width, resize_height));
				image_roi.copyTo(detect_roi);

				//cv to torch
				cv::Mat img_float;
				detect_mat.convertTo(img_float, CV_32F, 1.0 / 255);
				std::vector<cv::Mat> channels;
				cv::split(img_float, channels);
				channels[0] -= 0.406;
				channels[1] -= 0.457;
				channels[2] -= 0.480;
				cv::merge(channels, img_float);
				std::vector<torch::jit::IValue> inputs;
				torch::Tensor img_tensor = torch::CPU(torch::kFloat32).tensorFromBlob(img_float.data, { 1,img_float.rows, img_float.cols, 3 });
				img_tensor = img_tensor.permute({ 0,3,1,2 });
				torch::Tensor img_var = torch::autograd::make_variable(img_tensor, false).to(device_type);
				inputs.emplace_back(img_var);
				
				//begin 2d pose detect
				torch::Tensor output = module->forward(inputs).toTensor();
				
				std::cout << -start + clock() << std::endl;
				
				//get peak
				std::tuple<torch::Tensor, torch::Tensor> yM = torch::max(output[0], 2);
				std::tuple<torch::Tensor, torch::Tensor> xM = torch::max(output[0], 1);
				
				yM = torch::max(std::get<0>(yM), 1);
				xM = torch::max(std::get<0>(xM), 1);
				
				//to origin image
				at::Tensor pt_x = std::get<1>(xM) * det_width / fea_width;
				at::Tensor pt_y = std::get<1>(yM) * det_height / fea_height;
				pt_x = (pt_x - det_box.x) * rect2.width / det_box.width + rect2.x;
				pt_y = (pt_y - det_box.y) * rect2.height / det_box.height + rect2.y;

				if (pt_x.size(0) > 17)
				{
					for (int i = 17; i < 33; ++i)
					{
						cv::circle(origin_image, cv::Point(pt_x[i].item<int>(), pt_y[i].item<int>()), 2, cv::Scalar(0, 0, 255), 2);
					}
				}
				else if (pt_x.size(0) == 17)
				{
					for (int i = 0; i < 17; ++i)
					{
						cv::circle(origin_image, cv::Point(pt_x[i].item<int>(), pt_y[i].item<int>()), 2, cv::Scalar(0, 0, 255), 2);
					}
				}
				//draw 2d
				


				std::vector<float> vertexs;

				//init render model 
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


				//init 3d
				if (frame_id >= 1)
				{
					std::vector<float> tmp;
					if (pt_x.size(0) > 17)
					{
						for (int i = 0; i < 16; ++i)
						{
							tmp.push_back(pt_x[mapping2[i] + 17].item<float>());
							tmp.push_back(pt_y[mapping2[i] + 17].item<float>());
						}
					}
					else if (pt_x.size(0) == 17)
					{
						for (int i = 0; i < 16; ++i)
						{
							if (mapping1[i] != -1)
							{
								tmp.push_back(pt_x[mapping1[i]].item<float>());
								tmp.push_back(pt_y[mapping1[i]].item<float>());
							}
							else
							{
								tmp.push_back(0);
								tmp.push_back(0);
							}
						}
						tmp[0] = (tmp[1 * 2] + tmp[4 * 2]) / 2;
						tmp[1] = (tmp[1 * 2 + 1] + tmp[4 * 2 + 1]) / 2;
						tmp[8 * 2] = (tmp[10 * 2] + tmp[13 * 2]) / 2;
						tmp[8 * 2 + 1] = (tmp[10 * 2 + 1] + tmp[13 * 2 + 1]) / 2;
						tmp[7 * 2] = (tmp[9 * 2] + tmp[8 * 2]) / 2;
						tmp[7 * 2 + 1] = (tmp[9 * 2 + 1] + tmp[8 * 2 + 1]) / 2;
						
					}

					for (int i = 0; i < tmp.size(); ++i)
					{
						tmp[i] = (tmp[i] - means_2d[i]) / stds_2d[i];
					}

					std::vector<float> output;
					baseline.predict(tmp, output);
					vertexs.push_back(0);
					vertexs.push_back(-0);
					vertexs.push_back(-0);

					for (int i = 0; i < 16; ++i)
					{
						vertexs.push_back((output[i * 3] * stds_3d[i * 3] + means_3d[i * 3]) / 1000);
						vertexs.push_back((output[i * 3 + 1] * stds_3d[3 * i + 1] + means_3d[3 * i + 1]) / -1000);
						vertexs.push_back((output[i * 3 + 2] * stds_3d[3 * i + 2] + means_3d[3 * i + 2]) / -1000);
					}

					position_3d.push_back(vertexs);

				}

				std::cout << -start + clock() << std::endl;

				sprintf_s(txt_buffer, "%.1f", (1.0 / (-start + clock()) * 1000));
				start = clock();
				drawTxt(origin_image, "FPS:" + string(txt_buffer));
				cv::flip(origin_image, origin_image, 1);
				mcam.drawFrame(origin_image);
				if (vertexs.size() > 0)
				{
					meshes.render(vertexs, indics, curModel);
				}
				glfwSwapBuffers(window);
				glfwPollEvents();
			}
		} while (frame_id < numFrames && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
		glfwTerminate();

		return 0;
	}

	void AlphaBaseline::writePositionToJson(const std::string & path, const std::vector<std::vector<float>>& output_postition)
	{
		OutputDebugString(L"write json");
		OutputDebugString(L"\n");
		writeToJson(path, output_postition);
		OutputDebugString(L"write finish");
		OutputDebugString(L"\n");
	}

	int AlphaBaseline::predict_notShow(const string& video_path, const string& shader_dir, const string& mesh_dir, std::vector<std::vector<float>> position_3d)
	{
		position_3d.clear();
		std::cout << "loading video ..." << std::endl;
		cv::VideoCapture m_cam = cv::VideoCapture(video_path);
		if (!m_cam.isOpened())
		{
			std::cout << "null vedio" << std::endl;
			return -1;
		}
		std::cout << "video loaded ..." << std::endl;
		int frameHeight = (int)m_cam.get(CV_CAP_PROP_FRAME_HEIGHT);
		int frameWidth = (int)m_cam.get(CV_CAP_PROP_FRAME_WIDTH);
		int fps = (int)m_cam.get(CV_CAP_PROP_FPS);
		int numFrames = (int)m_cam.get(CV_CAP_PROP_FRAME_COUNT);
		std::cout << "frameW,frameH,fps,numFrame=" << frameHeight << "," << frameWidth << "," << fps << "," << numFrames << std::endl;


		std::cout << "start to inference ..." << std::endl;
		int frame_id = 0;
		cv::Mat frame;
		std::vector<float> front_pose;
		clock_t start;

		start = clock();

		do
		{
			if (!m_cam.read(frame)) {
				break;
			}

			++frame_id;

			cv::Mat origin_image = frame, resized_image_yolo;
			cv::cvtColor(origin_image, resized_image_yolo, cv::COLOR_RGB2BGR);
			cv::resize(resized_image_yolo, resized_image_yolo, cv::Size(input_image_size, input_image_size));

			//cv to torch
			cv::Mat img_float_yolo;
			resized_image_yolo.convertTo(img_float_yolo, CV_32F, 1.0 / 255);
			torch::Tensor img_tensor = torch::CPU(torch::kFloat32).tensorFromBlob(img_float_yolo.data, { 1, input_image_size, input_image_size, 3 });
			img_tensor = img_tensor.permute({ 0,3,1,2 });
			torch::Tensor img_var = torch::autograd::make_variable(img_tensor, false).to(device_type);
			//yolo detect
			torch::Tensor output = net.forward(img_var);
			torch::Tensor result = net.write_results(output, 80, 0.5, 0.6);
			std::cout << -start + clock() << std::endl;


			//2d pose detect
			if (result.dim() == 1 || result.size(0) == 0)
			{
				std::cout << "no object found" << std::endl;
			}
			else
			{

				int obj_num = result.size(0);


				float w_scale = float(origin_image.cols) / input_image_size;
				float h_scale = float(origin_image.rows) / input_image_size;
				result.select(1, 1).mul_(w_scale);
				result.select(1, 2).mul_(h_scale);
				result.select(1, 3).mul_(w_scale);
				result.select(1, 4).mul_(h_scale);

				auto result_data = result.accessor<float, 2>();


				cv::Mat resized_mat;
				cv::cvtColor(origin_image, origin_image, cv::COLOR_BGR2RGB);


				int max_score_index = 0;
				float max_score = 0;
				for (int i = 0; i < result.size(0); ++i)
				{
					if (result_data[i][5] > max_score)
					{
						max_score = result_data[i][5];
						max_score_index = i;
					}
				}

				//cv::rectangle(origin_image, cv::Point(result_data[max_score_index][1], result_data[max_score_index][2]), cv::Point(result_data[max_score_index][3], result_data[max_score_index][4]), cv::Scalar(0, 0, 255), 1, 1, 0);


				//resize box
				cv::Rect rect(result_data[max_score_index][1], result_data[max_score_index][2],
					result_data[max_score_index][3] - result_data[max_score_index][1] + 1,
					result_data[max_score_index][4] - result_data[max_score_index][2] + 1);
				result_data[max_score_index][1] = std::max(0.0, rect.x - rect.width * 0.3 / 2);
				result_data[max_score_index][2] = std::max(0.0, rect.y - rect.height * 0.3 / 2);
				result_data[max_score_index][3] = std::max(
					std::min(origin_image.cols - 1.0,
						result_data[max_score_index][3] + rect.width * 0.3 / 2),
					result_data[max_score_index][1] + 5.0);
				result_data[max_score_index][4] = std::max(
					std::min(origin_image.rows - 1.0,
						result_data[max_score_index][4] + rect.width * 0.3 / 2),
					result_data[max_score_index][2] + 5.0);


				cv::Rect rect2(result_data[max_score_index][1], result_data[max_score_index][2], result_data[max_score_index][3] - result_data[max_score_index][1] + 1, result_data[max_score_index][4] - result_data[max_score_index][2] + 1);




				//resize image
				float scale = resize_ratio(rect2.width, rect2.height, det_width, det_height);
				float resize_height = rect2.height * scale;
				float resize_width = rect2.width * scale;
				cv::Mat detect_mat(det_height, det_width, CV_8UC3, cv::Scalar(0, 0, 0));
				int center_point_x = detect_mat.cols / 2;
				int center_point_y = detect_mat.rows / 2;
				cv::Rect det_box(center_point_x - resize_width / 2, center_point_y - resize_height / 2, resize_width, resize_height);
				cv::Mat detect_roi = detect_mat(det_box);
				cv::Mat image_roi = origin_image(rect2);
				cv::resize(image_roi, image_roi, cv::Size(resize_width, resize_height));
				image_roi.copyTo(detect_roi);

				//cv to torch
				cv::Mat img_float;
				detect_mat.convertTo(img_float, CV_32F, 1.0 / 255);
				std::vector<cv::Mat> channels;
				cv::split(img_float, channels);
				channels[0] -= 0.406;
				channels[1] -= 0.457;
				channels[2] -= 0.480;
				cv::merge(channels, img_float);
				std::vector<torch::jit::IValue> inputs;
				torch::Tensor img_tensor = torch::CPU(torch::kFloat32).tensorFromBlob(img_float.data, { 1,img_float.rows, img_float.cols, 3 });
				img_tensor = img_tensor.permute({ 0,3,1,2 });
				torch::Tensor img_var = torch::autograd::make_variable(img_tensor, false).to(device_type);
				inputs.emplace_back(img_var);

				//begin 2d pose detect
				torch::Tensor output = module->forward(inputs).toTensor();

				std::cout << -start + clock() << std::endl;

				//get peak
				std::tuple<torch::Tensor, torch::Tensor> yM = torch::max(output[0], 2);
				std::tuple<torch::Tensor, torch::Tensor> xM = torch::max(output[0], 1);

				yM = torch::max(std::get<0>(yM), 1);
				xM = torch::max(std::get<0>(xM), 1);

				//to origin image
				at::Tensor pt_x = std::get<1>(xM) * det_width / fea_width;
				at::Tensor pt_y = std::get<1>(yM) * det_height / fea_height;
				pt_x = (pt_x - det_box.x) * rect2.width / det_box.width + rect2.x;
				pt_y = (pt_y - det_box.y) * rect2.height / det_box.height + rect2.y;

				if (pt_x.size(0) > 17)
				{
					for (int i = 17; i < 33; ++i)
					{
						cv::circle(origin_image, cv::Point(pt_x[i].item<int>(), pt_y[i].item<int>()), 2, cv::Scalar(0, 0, 255), 2);
					}
				}
				else if (pt_x.size(0) == 17)
				{
					for (int i = 0; i < 17; ++i)
					{
						cv::circle(origin_image, cv::Point(pt_x[i].item<int>(), pt_y[i].item<int>()), 2, cv::Scalar(0, 0, 255), 2);
					}
				}
				//draw 2d

				std::vector<float> vertexs;

				//init 3d
				if (frame_id >= 1)
				{
					std::vector<float> tmp;
					if (pt_x.size(0) > 17)
					{
						for (int i = 0; i < 16; ++i)
						{
							tmp.push_back(pt_x[mapping2[i] + 17].item<float>());
							tmp.push_back(pt_y[mapping2[i] + 17].item<float>());
						}
					}
					else if (pt_x.size(0) == 17)
					{
						for (int i = 0; i < 16; ++i)
						{
							if (mapping1[i] != -1)
							{
								tmp.push_back(pt_x[mapping1[i]].item<float>());
								tmp.push_back(pt_y[mapping1[i]].item<float>());
							}
							else
							{
								tmp.push_back(0);
								tmp.push_back(0);
							}
						}
						tmp[0] = (tmp[1 * 2] + tmp[4 * 2]) / 2;
						tmp[1] = (tmp[1 * 2 + 1] + tmp[4 * 2 + 1]) / 2;
						tmp[8 * 2] = (tmp[10 * 2] + tmp[13 * 2]) / 2;
						tmp[8 * 2 + 1] = (tmp[10 * 2 + 1] + tmp[13 * 2 + 1]) / 2;
						tmp[7 * 2] = (tmp[9 * 2] + tmp[8 * 2]) / 2;
						tmp[7 * 2 + 1] = (tmp[9 * 2 + 1] + tmp[8 * 2 + 1]) / 2;

					}

					for (int i = 0; i < tmp.size(); ++i)
					{
						tmp[i] = (tmp[i] - means_2d[i]) / stds_2d[i];
					}

					std::vector<float> output;
					baseline.predict(tmp, output);
					vertexs.push_back(0);
					vertexs.push_back(-0);
					vertexs.push_back(-0);

					for (int i = 0; i < 16; ++i)
					{
						vertexs.push_back((output[i * 3] * stds_3d[i * 3] + means_3d[i * 3]) / 1000);
						vertexs.push_back((output[i * 3 + 1] * stds_3d[3 * i + 1] + means_3d[3 * i + 1]) / -1000);
						vertexs.push_back((output[i * 3 + 2] * stds_3d[3 * i + 2] + means_3d[3 * i + 2]) / -1000);
					}

					position_3d.push_back(vertexs);

				}

				std::cout << -start + clock() << std::endl;
			}
		} while (frame_id < numFrames);
		glfwTerminate();

		return 0;
	}

	float AlphaBaseline::resize_ratio(const float & picture_width, const float & picture_height, const float & default_width, const float & default_height)
	{
		float widthRatio = default_width / picture_width;
		float heightRatio = default_height / picture_height;
		float ratio = 0;
		widthRatio < heightRatio ? ratio = widthRatio : ratio = heightRatio;
		return ratio;
	}

	void AlphaBaseline::drawPoint(cv::Mat & img, const std::vector<float>& pos, const int & joint_num)
	{
		for (int i = 0; i < joint_num; ++i) {

			int x = (pos[i * 2 + 0] + 0.5) * img.size().height;
			int y = (pos[i * 2 + 1] + 0.5) * img.size().width;
			for (int j = -2; j < 3; ++j) {
				for (int k = -2; k < 3; ++k) {
					if (x + j < 0 || x + j >= img.size().height || y + k >= img.size().width || y + k < 0) {
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

	void AlphaBaseline::drawTxt(cv::Mat& img, const string& txt)
	{
		cv::Size txt_size = cv::getTextSize(txt, font_face, font_scale, thickness, &text_line);
		cv::Point origin(0, txt_size.height);
		cv::putText(img, txt, origin, font_face, font_scale, cv::Scalar(0, 0, 255));
	
	}
















	void mouse_move_callback(GLFWwindow* window, double x, double y) {
		curX = x;
		curY = y;

		if (isMousePressed) {
			std::cout << "cursor is at (" << curX << ", " << curY << ")" << std::endl;
		}
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
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

	void SetOpenGLState() {
		// enable depth test and accept fragment if it closer to the camera than the former one
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void error_callback(int error, const char* description)
	{
		printf("glfwERROR: code %d, desc:%s\n", error, description);
	}

	GLFWwindow* InitWindow(float wndWidth, float wndHeight) {
		glfwSetErrorCallback(alphaBaseline::error_callback);
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
		glfwSetMouseButtonCallback(window, alphaBaseline::mouse_button_callback);
		glfwSetCursorPosCallback(window, alphaBaseline::mouse_move_callback);
		glfwSwapInterval(0);

		if (glewInit() != GLEW_OK) {
			std::cout << "Failed to initialize GLEW\n" << std::endl;
			glfwTerminate();
			return nullptr;
		}

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		return window;
	}


}
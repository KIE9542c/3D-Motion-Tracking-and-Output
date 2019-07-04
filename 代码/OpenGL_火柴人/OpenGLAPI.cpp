#include "OpenGLAPI.h"
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool OpenGLAPI::ReadPosition(const char* lFilename, std::vector<std::vector<QVector3D>>& lpos) {
	Json::CharReaderBuilder rbuilder;
	rbuilder["collectComments"] = false;
	Json::Value root;
	JSONCPP_STRING errs;

	std::fstream f;
	f.open(lFilename, std::ios::in);
	if (!f.is_open()) {
		std::cout << "Open json file error!" << std::endl;
		return false;
	}

	bool parse_ok = Json::parseFromStream(rbuilder, f, &root, &errs);
	if (!parse_ok) {
		std::cout << "Parse json file error!" << std::endl;
		return false;
	}
	else {
		try {
			for (int i = 0; i < root["bodies"].size(); i++)
			{
				std::cout << "Loading frame " << i << std::endl;
				std::vector<QVector3D> lFrame;
				std::vector<float> lPosition;
				for (int n = 0; n < root["bodies"][i]["position"].size(); n++)
				{
					lPosition.push_back(root["bodies"][i]["position"][n].asFloat());
					if ((n + 1) % 3 == 0) {
						lFrame.push_back(QVector3D(lPosition[0], lPosition[1], lPosition[2]));
						lPosition.clear();
					}
				}
				lpos.push_back(lFrame);
				lFrame.clear();
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

void OpenGLAPI::processVertice(std::vector<glm::vec3> &vertices, QVector3D base, QVector3D front) {
	glm::vec3 lbase = glm::vec3(base.x(), base.y(), base.z());
	glm::vec3 lfront = glm::vec3(front.x(), front.y(), front.z());
	glm::vec3 dir = lfront - lbase;
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), dir);
	vertices.push_back(lfront);
	glm::vec3 temp1;
	if (dir.z == 0) {
		temp1 = glm::vec3(1, -dir.x/dir.y, 0);
	}
	else {
		temp1 = glm::vec3(1, 1, (-dir.x - dir.y) / dir.z);
	}
	float scale = sqrt((pow(dir.x,2)+ pow(dir.y, 2) + pow(dir.z, 2)) /(pow(temp1.x,2)+ pow(temp1.y, 2)+ pow(temp1.z, 2)));
	glm::mat4 transscale = glm::mat4(1.0f);
	transscale = glm::scale(transscale, glm::vec3(scale/5, scale/5, scale/5));
	temp1 = transscale * glm::vec4(temp1,1);
	vertices.push_back(lbase + temp1);
	temp1 = (trans * glm::vec4(temp1,1));
	vertices.push_back(lbase + temp1);
	temp1 = (trans * glm::vec4(temp1, 1));
	vertices.push_back(lbase + temp1);
	temp1 = (trans * glm::vec4(temp1, 1));
	vertices.push_back(lbase + temp1);
	return;
}

void OpenGLAPI::processVertice_Vnect(std::vector<glm::vec3> &vertices, std::vector<std::vector<QVector3D>>& lpos) {
	processVertice(vertices, lpos[gFrame][1], lpos[gFrame][2]);
	processVertice(vertices, lpos[gFrame][2], lpos[gFrame][3]);
	processVertice(vertices, lpos[gFrame][3], lpos[gFrame][4]);
	processVertice(vertices, lpos[gFrame][4], lpos[gFrame][17]);
	processVertice(vertices, lpos[gFrame][1], lpos[gFrame][5]);
	processVertice(vertices, lpos[gFrame][5], lpos[gFrame][6]);
	processVertice(vertices, lpos[gFrame][6], lpos[gFrame][7]);
	processVertice(vertices, lpos[gFrame][7], lpos[gFrame][18]);
	processVertice(vertices, lpos[gFrame][1], lpos[gFrame][16]);
	processVertice(vertices, lpos[gFrame][16], lpos[gFrame][0]);
	processVertice(vertices, lpos[gFrame][14], lpos[gFrame][8]);
	processVertice(vertices, lpos[gFrame][8], lpos[gFrame][9]);
	processVertice(vertices, lpos[gFrame][9], lpos[gFrame][10]);
	processVertice(vertices, lpos[gFrame][10], lpos[gFrame][19]);
	processVertice(vertices, lpos[gFrame][14], lpos[gFrame][11]);
	processVertice(vertices, lpos[gFrame][11], lpos[gFrame][12]);
	processVertice(vertices, lpos[gFrame][12], lpos[gFrame][13]);
	processVertice(vertices, lpos[gFrame][13], lpos[gFrame][20]);
	processVertice(vertices, lpos[gFrame][14], lpos[gFrame][15]);
	processVertice(vertices, lpos[gFrame][15], lpos[gFrame][1]);
}

void OpenGLAPI::processVertice_OpenMMD(std::vector<glm::vec3> &vertices, std::vector<std::vector<QVector3D>>& lpos) {
	processVertice(vertices, lpos[gFrame][8], lpos[gFrame][14]);
	processVertice(vertices, lpos[gFrame][14], lpos[gFrame][15]);
	processVertice(vertices, lpos[gFrame][15], lpos[gFrame][16]);
	processVertice(vertices, lpos[gFrame][8], lpos[gFrame][11]);
	processVertice(vertices, lpos[gFrame][11], lpos[gFrame][12]);
	processVertice(vertices, lpos[gFrame][12], lpos[gFrame][13]);
	processVertice(vertices, lpos[gFrame][8], lpos[gFrame][9]);
	processVertice(vertices, lpos[gFrame][9], lpos[gFrame][10]);
	processVertice(vertices, lpos[gFrame][0], lpos[gFrame][1]);
	processVertice(vertices, lpos[gFrame][1], lpos[gFrame][2]);
	processVertice(vertices, lpos[gFrame][2], lpos[gFrame][3]);
	processVertice(vertices, lpos[gFrame][0], lpos[gFrame][4]);
	processVertice(vertices, lpos[gFrame][4], lpos[gFrame][5]);
	processVertice(vertices, lpos[gFrame][5], lpos[gFrame][6]);
	processVertice(vertices, lpos[gFrame][0], lpos[gFrame][7]);
	processVertice(vertices, lpos[gFrame][7], lpos[gFrame][8]);
}

void OpenGLAPI::initialize() {

	gFrame = 0;

}
void OpenGLAPI::singleVideo_Vnect(){

	float scale = 0.2 / (gPosition1[0][15] - gPosition1[0][14]).length();
	for (size_t i = 0; i < gPosition1.size(); i++)
	{
		for (size_t n = 0; n < gPosition1[i].size(); n++)
		{
			gPosition1[i][n] = (gPosition1[i][n])*scale;
		}
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}


	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glEnable(GL_DEPTH_TEST);

	ourShader = Shader("./shader/shader.vs", "./shader/shader.fs");

	std::vector<unsigned int> indices;
	for (size_t i = 0; i < 20; i++)
	{
		indices.push_back(5 * i);
		indices.push_back(5 * i + 1);
		indices.push_back(5 * i +2 );
		indices.push_back(5 * i);
		indices.push_back(5 * i+2);
		indices.push_back(5 * i+3);
		indices.push_back(5 * i);
		indices.push_back(5 * i+3);
		indices.push_back(5 * i+4);
		indices.push_back(5 * i);
		indices.push_back(5 * i+4);
		indices.push_back(5 * i+1);
		indices.push_back(5 * i+1);
		indices.push_back(5 * i+2);
		indices.push_back(5 * i+3);
		indices.push_back(5 * i+3);
		indices.push_back(5 * i+4);
		indices.push_back(5 * i+1);
	}
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		std::cout<<"+1s"<<std::endl;
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::vector<glm::vec3> vertices;
		processVertice_Vnect(vertices, gPosition1);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		
		glBindVertexArray(0);

		ourShader.use();
		ourShader.setVec3("color", 1.0f, 1.0f, 1.0f);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", glm::value_ptr(projection));
		ourShader.setMat4("view", glm::value_ptr(view));

		glm::mat4 model;
		ourShader.setMat4("model", glm::value_ptr(model));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		gFrame++;
		if (gFrame >= gPosition1.size())
			gFrame = 0;
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	gFrame = 0;
	return ;
}

void OpenGLAPI::singleVideo_OpenMMD() {

	float scale =0.2/(gPosition1[0][7] - gPosition1[0][0]).length();
	for (size_t i = 0; i < gPosition1.size(); i++)
	{
		for (size_t n = 0; n < gPosition1[i].size(); n++)
		{
			gPosition1[i][n] = (gPosition1[i][n])*scale;
		}
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}


	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glEnable(GL_DEPTH_TEST);

	ourShader = Shader("./shader/shader.vs", "./shader/shader.fs");

	std::vector<unsigned int> indices;
	for (size_t i = 0; i < 16; i++)
	{
		indices.push_back(5 * i);
		indices.push_back(5 * i + 1);
		indices.push_back(5 * i + 2);
		indices.push_back(5 * i);
		indices.push_back(5 * i + 2);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i + 4);
		indices.push_back(5 * i);
		indices.push_back(5 * i + 4);
		indices.push_back(5 * i + 1);
		indices.push_back(5 * i + 1);
		indices.push_back(5 * i + 2);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i + 4);
		indices.push_back(5 * i + 1);
	}
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		std::cout << "+1s" << std::endl;
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::vector<glm::vec3> vertices;
		processVertice_OpenMMD(vertices, gPosition1);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

		glBindVertexArray(0);

		ourShader.use();
		ourShader.setVec3("color", 1.0f, 1.0f, 1.0f);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", glm::value_ptr(projection));
		ourShader.setMat4("view", glm::value_ptr(view));

		glm::mat4 model;
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
//		model = glm::scale(model, glm::vec3(0.003, 0.003, 0.003));
		ourShader.setMat4("model", glm::value_ptr(model));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		gFrame++;
		if (gFrame >= gPosition1.size())
			gFrame = 0;
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	gFrame = 0;
	return;
}

void OpenGLAPI::doubleVideo_Vnect() {
	float scale = 0.2 / (gPosition1[0][15] - gPosition1[0][14]).length();
	for (size_t i = 0; i < gPosition1.size(); i++)
	{
		for (size_t n = 0; n < gPosition1[i].size(); n++)
		{
			gPosition1[i][n] = gPosition1[i][n]*scale;
		}
	}

	scale = 0.2 / (gPosition2[0][15] - gPosition2[0][14]).length();
	for (size_t i = 0; i < gPosition2.size(); i++)
	{
		for (size_t n = 0; n < gPosition2[i].size(); n++)
		{
			gPosition2[i][n] = gPosition2[i][n] * scale + QVector3D(1, 0, 0);
		}
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}


	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glEnable(GL_DEPTH_TEST);

	ourShader = Shader("./shader/shader.vs", "./shader/shader.fs");

	std::vector<unsigned int> indices;
	for (size_t i = 0; i < 40; i++)
	{
		indices.push_back(5 * i);
		indices.push_back(5 * i + 1);
		indices.push_back(5 * i + 2);
		indices.push_back(5 * i);
		indices.push_back(5 * i + 2);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i + 4);
		indices.push_back(5 * i);
		indices.push_back(5 * i + 4);
		indices.push_back(5 * i + 1);
		indices.push_back(5 * i + 1);
		indices.push_back(5 * i + 2);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i + 4);
		indices.push_back(5 * i + 1);
	}
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		std::cout << "+1s" << std::endl;
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::vector<glm::vec3> vertices;
		processVertice_Vnect(vertices, gPosition1);
		processVertice_Vnect(vertices, gPosition2);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

		glBindVertexArray(0);

		ourShader.use();
		ourShader.setVec3("color", 1.0f, 1.0f, 1.0f);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", glm::value_ptr(projection));
		ourShader.setMat4("view", glm::value_ptr(view));

		glm::mat4 model;
		ourShader.setMat4("model", glm::value_ptr(model));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		gFrame++;
		if (gFrame >= gPosition1.size() || gFrame >= gPosition2.size())
			gFrame = 0;
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	gFrame = 0;
	return;
}

void OpenGLAPI::doubleVideo_OpenMMD() {
	float scale = 0.2 / (gPosition1[0][7] - gPosition1[0][0]).length();
	for (size_t i = 0; i < gPosition1.size(); i++)
	{
		for (size_t n = 0; n < gPosition1[i].size(); n++)
		{
			gPosition1[i][n] = gPosition1[i][n] * scale;
		}
	}

	scale = 0.2 / (gPosition2[0][7] - gPosition2[0][0]).length();
	for (size_t i = 0; i < gPosition2.size(); i++)
	{
		for (size_t n = 0; n < gPosition2[i].size(); n++)
		{
			gPosition2[i][n] = gPosition2[i][n] * scale + QVector3D(1, 0, 0);
		}
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}


	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glEnable(GL_DEPTH_TEST);

	ourShader = Shader("./shader/shader.vs", "./shader/shader.fs");

	std::vector<unsigned int> indices;
	for (size_t i = 0; i < 32; i++)
	{
		indices.push_back(5 * i);
		indices.push_back(5 * i + 1);
		indices.push_back(5 * i + 2);
		indices.push_back(5 * i);
		indices.push_back(5 * i + 2);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i + 4);
		indices.push_back(5 * i);
		indices.push_back(5 * i + 4);
		indices.push_back(5 * i + 1);
		indices.push_back(5 * i + 1);
		indices.push_back(5 * i + 2);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i + 3);
		indices.push_back(5 * i + 4);
		indices.push_back(5 * i + 1);
	}
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		std::cout << "+1s" << std::endl;
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::vector<glm::vec3> vertices;
		processVertice_OpenMMD(vertices, gPosition1);
		processVertice_OpenMMD(vertices, gPosition2);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

		glBindVertexArray(0);

		ourShader.use();
		ourShader.setVec3("color", 1.0f, 1.0f, 1.0f);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", glm::value_ptr(projection));
		ourShader.setMat4("view", glm::value_ptr(view));

		glm::mat4 model;
		ourShader.setMat4("model", glm::value_ptr(model));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		gFrame++;
		if (gFrame >= gPosition1.size()||gFrame>=gPosition2.size())
			gFrame = 0;
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	gFrame = 0;
	return;
}


void OpenGLAPI::processInput(GLFWwindow *window) {
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = lastX - xPos;	//别忘了，在窗口中，左边的坐标小于右边的坐标，而我们需要一个正的角度
	float yoffset = lastY - yPos;	//同样，在窗口中，下面的坐标大于上面的坐标，而我们往上抬头的时候需要一个正的角度
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

int main() {
	OpenGLAPI test("C:\\Users\\9\\Desktop\\3d_posititon.json");
	test.singleVideo_Vnect();
}

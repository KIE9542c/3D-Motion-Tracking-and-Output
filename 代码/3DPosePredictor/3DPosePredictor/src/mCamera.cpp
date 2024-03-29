#include "mCamera.h"
#include "mDefs.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
using namespace alphaBaseline;
mCamera::~mCamera() {
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
}
mCamera::mCamera(int wndWidth, int wndHeight,float rW, float rH, mShader *camShader, bool isOpenCamera) {
    this->wndWidth = wndWidth;
    this->wndHeight = wndHeight;
    this->camShader = camShader;
    this->isOpenCamera = isOpenCamera;
	this->ratio_w = rW;
	this->ratio_h = rH;
    glGenVertexArrays(1, &VAO);
    
    if (isOpenCamera) {
        m_camera = cv::VideoCapture(0);
    }
}
bool mCamera::init() {
    glBindVertexArray(VAO);
    if (isOpenCamera && !m_camera.isOpened()) {
        std::cout << "ERROR: Camera init failed!" << std::endl;
        return false;
    }
    if (isOpenCamera) {
        m_camera.set(CV_CAP_PROP_FRAME_WIDTH, wndWidth);
        m_camera.set(CV_CAP_PROP_FRAME_HEIGHT, wndHeight);
    }
    initGLFrame();
    glBindVertexArray(0);
    return true;
}

void mCamera::initGLFrame() {
    float scale_size = 15*glm::tan(glm::radians(base_vof/2))/(ratio_h/2);
    glm::mat4 projection = glm::perspective(glm::radians(base_vof), ratio_w / ratio_h, 0.1f, 100.0f);
    // camera matrix
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::scale(model, glm::vec3(scale_size, scale_size,  1));
    // model matrix
    MVP = projection*view*model;

    textureID = genTexture();

    static const GLfloat g_vertex_buffer_data[] = {
        -ratio_w/2, ratio_h/2, -10.0f,
        -ratio_w/2, -ratio_h/2, -10.0f,
        ratio_w/2, -ratio_h/2, -10.0f,
        ratio_w/2, -ratio_h/2, -10.0f,
        ratio_w/2, ratio_h/2, -10.0f,
        -ratio_w/2, ratio_h/2, -10.0f
    };
    static const GLfloat uv_data[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };
 
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv_data), uv_data, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
}
GLuint mCamera::genTexture() {

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    return texture;
}
void mCamera::setTextureData(cv::Mat & frame) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    cv::flip(frame, frame, 0);
	uchar* t = frame.ptr(0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wndWidth, wndHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, t);
    glGenerateMipmap(GL_TEXTURE_2D);
}
void mCamera::drawFrame() {
    if (!isOpenCamera) {
        std::cout << "ERROR: Camera is not opened!" << std::endl;
        return;
    }
    cv::Mat frame;
    glBindVertexArray(VAO);

    camShader->use();
    camShader->setVal("MVP", MVP);
    if (!m_camera.read(frame)) {
        std::cout << "ERROR:mCamera->drawFrame: frame read failed!" << std::endl;
        return;
    }
    setTextureData(frame);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    camShader->setVal("myTextureSampler", 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 6); // 第三个参数的含义是 顶点的数目

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}
void mCamera::drawFrame(cv::Mat &frame) {
    glBindVertexArray(VAO);

    camShader->use();
    camShader->setVal("MVP", MVP);
    setTextureData(frame);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    camShader->setVal("myTextureSampler", 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 6); // 第三个参数的含义是 顶点的数目

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

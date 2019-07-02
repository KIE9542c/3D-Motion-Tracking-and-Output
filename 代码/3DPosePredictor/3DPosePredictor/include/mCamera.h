#pragma once
#include <iostream>
#include "mShader.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include "mDefs.h"
namespace alphaBaseline
{
	class mCamera {
	public:
		cv::VideoCapture m_camera;
		int wndWidth;
		int wndHeight;
		float ratio_w;
		float ratio_h;
		mCamera(int wndWidth, int wndHeight, float rW, float rH, mShader* camShader, bool isOpenCamera = true);
		~mCamera();
		bool init();
		void drawFrame();
		void drawFrame(cv::Mat& frame);
	private:
		GLuint VAO;
		mShader* camShader;
		GLuint vertexBuffer;
		GLuint uvBuffer;
		glm::mat4 MVP;
		GLuint textureID;
		GLuint samplerID;
		bool isOpenCamera;
		void initGLFrame();
		GLuint genTexture();
		void setTextureData(cv::Mat& frame);

	};
}
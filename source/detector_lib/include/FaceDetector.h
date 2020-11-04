#pragma once

#include <opencv2/opencv.hpp>

#if defined(_WIN32)
	#ifdef FACE_DETECTOR_EXPORTS
		#define FACE_DETECTOR_API __declspec(dllexport)
	#else
		#define FACE_DETECTOR_API __declspec(dllimport)
	#endif
#else
	#define FACE_DETECTOR_API
#endif


cv::CascadeClassifier FaceDetector;

extern "C" {
	FACE_DETECTOR_API bool InitializeFaceDetector();
	FACE_DETECTOR_API std::vector<cv::Rect> DetectFaces(const cv::Mat&, const std::string&);
}
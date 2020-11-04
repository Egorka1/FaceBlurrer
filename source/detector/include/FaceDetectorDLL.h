#pragma once

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

#if _WIN32
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif


class FaceDetectorDLL final {
public:
	FaceDetectorDLL(const char*, int = 2) noexcept;
	~FaceDetectorDLL();

	std::vector<cv::Rect> CallDetectFaces(const cv::Mat&, const std::string&) const noexcept;

private:
	bool LoadLib(const char*, int) noexcept;
	bool FreeLib() noexcept;
	void* GetFunc(const char*) noexcept;

private:
	typedef bool(*Initializer)();
	typedef std::vector<cv::Rect>(*Detector)(const cv::Mat&, const std::string&);

	void* m_hInstance;

	Initializer m_fInitialize;
	Detector m_fDetect;
};
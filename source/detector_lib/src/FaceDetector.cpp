#include "FaceDetector.h"


bool InitializeFaceDetector() {
	return FaceDetector.load("FaceCascade.xml");
}

std::vector<cv::Rect> DetectFaces(const cv::Mat& image, const std::string& image_path) noexcept {
	if (image.empty()) {
		printf("[INVALID IMAGE]: %s\n", image_path.c_str());
		return {};
	}

	cv::Mat preprocessed;
	cv::cvtColor(image, preprocessed, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> faces;
	FaceDetector.detectMultiScale(preprocessed, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

	printf("[DONE]: %s - %d face(s)\n", image_path.c_str(), faces.size());

	return faces;
}
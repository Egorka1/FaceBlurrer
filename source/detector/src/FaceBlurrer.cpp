#include "FaceDetectorDLL.h"
#include "JsonWriter.h"
#include "Utils.h"


int main(int argc, char** argv) {
	std::string base_dir = Utils::ParseCommandLine(argc, argv);
	if (!boost::filesystem::is_directory(base_dir)) {
		std::cerr << "Directory " << base_dir << " doesn't exist!\n";
		return EXIT_FAILURE;
	}

	std::string result_filename;
	#if _WIN32
		result_filename = "\\result.json";
	#else
		result_filename = "/result.json";
	#endif

	const FaceDetectorDLL detector("detector_lib");
	JsonWriter writer(base_dir + result_filename);

	for (const boost::filesystem::directory_entry& file : boost::filesystem::recursive_directory_iterator(base_dir)) {
		if (Utils::IsImage(file)) {
			const std::string image_path = file.path().string();
			const std::string output_path = Utils::GetOutputImagePath(file.path());

			cv::Mat image = cv::imread(image_path);

			const std::vector<cv::Rect> faces = detector.CallDetectFaces(image, image_path);
			for (const cv::Rect& face : faces) {
				cv::Mat face_region = image(face);
				cv::GaussianBlur(face_region, face_region, cv::Size(), 7.);
			}

			cv::resize(image, image, cv::Size(), .5, .5, cv::INTER_CUBIC);
			cv::imwrite(output_path, image);

			writer.AddImageResults(image_path, output_path, faces);
		}
	}
	
	return EXIT_SUCCESS;
}
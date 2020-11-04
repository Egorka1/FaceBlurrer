#include "FaceDetectorDLL.h"
#include "JsonWriter.h"

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/program_options.hpp>


static bool IsImage(const boost::filesystem::directory_entry& file_path) {
	const static boost::regex exp("\.(jpe?g|png|webp|bmp)$");

	boost::smatch match;
	return boost::regex_search(file_path.path().filename().string(), match, exp);
}

static std::string GetOutputImagePath(const boost::filesystem::path& path) {
	const std::string dir_name = path.string().substr(0, path.string().find_last_of("/\\") + 1), image_name = path.stem().string();
	return dir_name + image_name + "_out.jpg";
}

int main(int argc, char** argv) {
	std::string base_dir;
	try {
		boost::program_options::options_description desc("Allowed options:");
		desc.add_options()
			("help", "Help with using")
			("d", boost::program_options::value<std::string>(), "Path to directory with images");

		boost::program_options::variables_map vm;
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
		boost::program_options::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << '\n';
			return EXIT_FAILURE;
		}

		base_dir = vm["d"].as<std::string>();
	}
	catch (const boost::program_options::error& error) {
		std::cerr << error.what() << '\n';
		system("pause");
		return EXIT_FAILURE;
	}

	if (!boost::filesystem::is_directory(base_dir)) {
		std::cerr << "Directory " << base_dir << " doesn't exist!\n";
		system("pause");
		return EXIT_FAILURE;
	}

	const FaceDetectorDLL detector("detector_lib");
	JsonWriter writer(base_dir + "//result.json");

	for (const boost::filesystem::directory_entry& file : boost::filesystem::recursive_directory_iterator(base_dir)) {
		if (IsImage(file)) {
			const std::string image_path = file.path().string();
			const std::string output_path = GetOutputImagePath(file.path());

			cv::Mat image = cv::imread(image_path);

			const std::vector<cv::Rect> faces = detector.CallDetectFaces(image, image_path);
			for (const cv::Rect& face : faces) {
				cv::Mat face_region = image(face);
				cv::GaussianBlur(face_region, face_region, cv::Size(), 7.);
			}

			cv::resize(image, image, cv::Size(), .5, .5, cv::INTER_CUBIC);
			//cv::imwrite(output_path, image);

			writer.AddImageResults(image_path, output_path, faces);
		}
	}
	
	system("pause");
	return 0;
}
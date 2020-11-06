#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/program_options.hpp>


namespace Utils {
	static bool IsImage(const boost::filesystem::directory_entry& file_path) noexcept {
		const static boost::regex exp("\.(jpe?g|png|webp|bmp)$");

		boost::smatch match;
		return boost::regex_search(file_path.path().filename().string(), match, exp);
	}

	static std::string GetOutputImagePath(const boost::filesystem::path& path) noexcept {
		const std::string dir_name = path.string().substr(0, path.string().find_last_of("/\\") + 1), image_name = path.stem().string();
		return dir_name + image_name + "_out.jpg";
	}

	// Returns path to directory with images
	static std::string ParseCommandLine(int argc, char** argv) noexcept {
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
				exit(EXIT_SUCCESS);
			}

			base_dir = vm["d"].as<std::string>();
		}
		catch (const boost::program_options::error& error) {
			std::cerr << error.what() << '\n';
			#if _WIN32
				system("pause");
			#endif
			exit(EXIT_FAILURE);
		}

		return base_dir;
	}
}
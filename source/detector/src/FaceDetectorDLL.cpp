#include "FaceDetectorDLL.h"


FaceDetectorDLL::FaceDetectorDLL(const char* dll_name, int mode) noexcept {
	if (!LoadLib(dll_name, mode)) {
		std::cerr << "Library loading failed!\n";
		#if _WIN32
			system("pause");
		#endif
		exit(EXIT_FAILURE);
	}

	m_fInitialize = (Initializer)GetFunc("InitializeFaceDetector");
	if (!m_fInitialize) {
		std::cerr << "Initializer GetProcAddress failed!\n";
		#if _WIN32
			system("pause");
		#endif
		exit(EXIT_FAILURE);
	}
	
	m_fDetect = (Detector)GetFunc("DetectFaces");
	if (!m_fDetect) {
		std::cerr << "Detector GetProcAddress failed!\n";
		#if _WIN32
			system("pause");
		#endif
		exit(EXIT_FAILURE);
	}

	if (!m_fInitialize()) {
		std::cerr << "Initialize detector failed\n!";
		#if _WIN32
			system("pause");
		#endif
		exit(EXIT_FAILURE);
	}
}
FaceDetectorDLL::~FaceDetectorDLL() {
	if (m_hInstance) {
		FreeLib();
	}
}

bool FaceDetectorDLL::LoadLib(const char* dll_name, int mode) noexcept {
	#if _WIN32
		std::string dll_path = std::string(dll_name) + ".dll";
		m_hInstance = (void*)LoadLibrary(dll_path.c_str());
	#else
		std::string dll_path = "lib" + std::string(dll_name) + ".so";
		m_hInstance = dlopen(dll_path.c_str(), mode);
	#endif

	return m_hInstance != nullptr;
}
bool FaceDetectorDLL::FreeLib() noexcept {
	#if _WIN32
		return FreeLibrary((HINSTANCE)m_hInstance);
	#else
		return dlclose(m_hInstance);
	#endif
}
void* FaceDetectorDLL::GetFunc(const char* func_name) noexcept {
	#if _WIN32
		return (void*)GetProcAddress((HINSTANCE)m_hInstance, func_name);
	#else
		return dlsym(m_hInstance, func_name);
	#endif
}

std::vector<cv::Rect> FaceDetectorDLL::CallDetectFaces(const cv::Mat& image, const std::string& image_path) const noexcept {
	return m_fDetect(image, image_path);
}
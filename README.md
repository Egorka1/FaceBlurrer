# FaceBlurrer

>***Pre requirements:***
1. CMake >= 3.14
2. OpenCV >= 3.0 (optional)
3. Boost >= 1.63 (optional)
4. Any C++ compiler

If OpenCV or/and Boost not builded then the build from sources will start automatically.\
Supported only Release configuration.


>***Installation guide:***
* Create temporary directory for build files:
	```
	mkdir build
	```
* Configure project (OpenCV_DIR is optional):
	```
	cmake -DCMAKE_GENERATOR_PLATFORM=<platform type> -DCMAKE_BUILD_TYPE=Release -DOpenCV_DIR=<path to builded OpenCV> -Bbuild
	```
* Build and install detector:
	```
	cmake --build build --config Release
	```
* Remove temporary directory (optional):
	* Windows:
		```
		rmdir /s/q build
		```
	* Unix:
		```
		rm -rf build
		```
* Run detector:
	* Windows:
		```
		detector.exe --d <path to directory with images>
		```
	* Unix:
		```
		./detector --d <path to directory with images>
		```
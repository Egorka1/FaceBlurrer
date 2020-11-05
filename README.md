# FaceBlurrer

>***Installation guide for Windows:***

* Create temporary directory for build files:

`mkdir build`

* Configure project:

	* With OpenCV already builded:

`cmake -DCMAKE_GENERATOR_PLATFORM=<platform type: x64, x86> -DCMAKE_BUILD_TYPE=Release -DOpenCV_DIR=<path to builded OpenCV> -Bbuild`

	* Without OpenCV builded:
		
`cmake -DCMAKE_GENERATOR_PLATFORM=<platform type: x64, x86> -DCMAKE_BUILD_TYPE=Release -Bbuild`

* Build detector:
	
`cmake --build build --config Release`

* Install OpenCV (if not installed):
	
`cmake --build build/source/opencv-4.5.0 --target install --config Release`

* Install detector:

`cmake --build build --target install --config Release`

* Remove temporary directory:

`rmdir /s/q build`

* Run detector:

`detector.exe --d <path to directory with images>`
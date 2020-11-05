# FaceBlurrer

**Installation guide:**

>***Windows:***
**1.** Create temporary directory for build files:

    `mkdir build`
**2.** Configure project setting platform and build type:

	*2.1.* With OpenCV already builded:

		`cmake -DCMAKE_GENERATOR_PLATFORM=<platform type: x64, x86> -DCMAKE_BUILD_TYPE=Release -DOpenCV_DIR=<path to builded OpenCV> -Bbuild`
	*2.2.* Without OpenCV builded:
		
		`cmake -DCMAKE_GENERATOR_PLATFORM=<platform type: x64, x86> -DCMAKE_BUILD_TYPE=Release -Bbuild`
**3.** Build detector setting configuration type:
	
	`cmake --build build --config Release`
**4.** Install OpenCV (if not installed):
	
	`cmake --build build/source/opencv-4.5.0 --target install --config Release`
**5.** Install detector:

	`cmake --build build --target install --config Release`
**6.** Remove temporary directory:

	`rmdir /s/q build`
**7.** Run detector with root directory parameter:

	`detector.exe -d <dir_path>`
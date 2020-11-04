# FaceBlurrer

**Installation guide:**

>***Windows:***
* Create temporary directory for build files:

    `mkdir build`
* Configure project setting platform and build type:

    `cmake -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release -Bbuild`
* Build detector setting configuration type:

    `cmake --build build --config Release`
* Install OpenCV:

    `cmake --build build/source/opencv-4.5.0 --target install --config Release`
* Install detector:

    `cmake --build build --target install --config Release`
* Remove temporary directory:

    `rmdir /s/q build`

* Run detector with root directory parameter:

    `detector/detector.exe -d <dir_path>`
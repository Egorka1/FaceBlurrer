# FaceBlurrer

Installation guide:

Windows:
- Create temporary directory for build files:
    FaceDetector: mkdir build
- Configure project setting platform and build type:
    FaceDetector: cmake -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release -Bbuild
- Build detector setting configuration type:
    FaceDetector: cmake --build build --config Release
- Install OpenCV:
    FaceDetector: cmake --build build/source/opencv-4.5.0 --target install --config Release
- Install detector:
    FaceDetector: cmake --build build --target install --config Release
- Remove temporary directory:
    rmdir /s/q build
- Run detector with root directory parameter:
    detector/detector.exe <dir_path>
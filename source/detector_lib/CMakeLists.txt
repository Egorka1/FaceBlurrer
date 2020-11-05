include_directories(include/)

add_library(detector_lib SHARED src/FaceDetector.cpp)
target_link_libraries(detector_lib ${OpenCV_LIBS})

set_target_properties(detector_lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY 	    	${DETECTOR_BINARY_DIR})
set_target_properties(detector_lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${DETECTOR_BINARY_DIR})
set_target_properties(detector_lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${DETECTOR_BINARY_DIR})
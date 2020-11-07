include_directories(include/)
add_library(detector_lib SHARED src/FaceDetector.cpp)

if(NOT OpenCV_FOUND)
	add_custom_command(
    		TARGET detector_lib PRE_BUILD
		COMMAND cmake --build ${CMAKE_BINARY_DIR}/source/opencv-4.5.0/ --config Release
    		COMMAND cmake --install ${CMAKE_BINARY_DIR}/source/opencv-4.5.0/ --config Release
    		COMMENT "Building and installing OpenCV-4.5.0..."
	)
endif()

target_link_libraries(detector_lib opencv_world)

set_target_properties(detector_lib PROPERTIES LIBRARY_OUTPUT_DIRECTORY 	    	${DETECTOR_BINARY_DIR})
set_target_properties(detector_lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY 	    	${DETECTOR_BINARY_DIR})
set_target_properties(detector_lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${DETECTOR_BINARY_DIR})
set_target_properties(detector_lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${DETECTOR_BINARY_DIR})

add_custom_command(
	TARGET detector_lib POST_BUILD
	COMMAND cmake --install ${CMAKE_BINARY_DIR}/source/detector_lib/ --config Release
	COMMENT "Building detector_lib..."
)
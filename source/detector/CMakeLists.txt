include_directories(include/)
add_executable(detector
	src/FaceBlurrer.cpp
	src/FaceDetectorDLL.cpp
	src/JsonWriter.cpp
)

if(NOT OpenCV_FOUND)
	add_dependencies(detector OpenCV_install)
endif()

target_link_libraries(detector ${CMAKE_DL_LIBS})
target_link_libraries(detector opencv_world)
target_link_libraries(detector Boost::boost)
target_link_libraries(detector Boost::filesystem)
target_link_libraries(detector Boost::regex)
target_link_libraries(detector Boost::program_options)

set_target_properties(detector PROPERTIES RUNTIME_OUTPUT_DIRECTORY 	    ${DETECTOR_BINARY_DIR})
set_target_properties(detector PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${DETECTOR_BINARY_DIR})
set_target_properties(detector PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${DETECTOR_BINARY_DIR})

add_custom_command(
	TARGET detector POST_BUILD
	COMMAND cmake --install ${CMAKE_BINARY_DIR}/source/detector/ --config Release
	COMMAND ${CMAKE_COMMAND} -E copy ${OPENCV_WORLD_INSTALL_PATH} ${DETECTOR_BINARY_DIR}
	COMMENT "Copying ${OPENCV_WORLD_INSTALL_PATH} to detector directory"
)
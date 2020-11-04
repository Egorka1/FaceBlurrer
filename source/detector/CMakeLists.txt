include_directories(${OPENCV_INCLUDE_INSTALL_PATH})
link_directories(${OPENCV_LIB_INSTALL_PATH})

include_directories(include/)
add_executable(detector
	src/FaceBlurrer.cpp
	src/FaceDetectorDLL.cpp
	src/JsonWriter.cpp
)

target_link_libraries(detector opencv_world450)
target_link_libraries(detector Boost::boost)
target_link_libraries(detector Boost::filesystem)
target_link_libraries(detector Boost::regex)
target_link_libraries(detector Boost::program_options)

set_target_properties(detector PROPERTIES RUNTIME_OUTPUT_DIRECTORY 	    ${DETECTOR_BINARY_DIR})
set_target_properties(detector PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${DETECTOR_BINARY_DIR})
set_target_properties(detector PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${DETECTOR_BINARY_DIR})

if (WIN32)
  set(OPENCV_WORLD_LIB "opencv_world450.dll")
else()
  set(OPENCV_WORLD_LIB "opencv_world450.so")
endif()

add_custom_target(copy_dll
  COMMAND ${CMAKE_COMMAND} -E copy ${OPENCV_BIN_INSTALL_PATH}${OPENCV_WORLD_LIB} ${DETECTOR_BINARY_DIR}
)
add_dependencies(detector copy_dll)


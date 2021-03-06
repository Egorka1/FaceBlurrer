add_custom_target(OpenCV_install
	COMMAND cmake --build ${CMAKE_BINARY_DIR}/source/opencv-4.5.0/ --config Release
    	COMMAND cmake --install ${CMAKE_BINARY_DIR}/source/opencv-4.5.0/ --config Release
)

find_package(OpenCV COMPONENTS opencv_world)
if(NOT OpenCV_FOUND)
	message(STATUS "OpenCV wasn't found. Installation of OpenCV-4.5.0 started...")

	set(BUILD_DOCS 		 		FALSE)
	set(BUILD_EXAMPLES 	 		FALSE)
	set(BUILD_TESTS 	 		FALSE)
	set(BUILD_PERF_TESTS 	 		FALSE)
	set(BUILD_opencv_java 	 		FALSE)
	set(BUILD_opencv_python  		FALSE)
	set(BUILD_opencv_world 	 		ON)
	set(WITH_FFMPEG 	 		FALSE)
	set(OpenCV_BINARY_DIR       		${CMAKE_INSTALL_PREFIX}/opencv/build/)
	set(OPENCV_BIN_INSTALL_PATH       	${OpenCV_BINARY_DIR}bin/)
	set(OPENCV_INCLUDE_INSTALL_PATH       	${OpenCV_BINARY_DIR}include/)
	set(OPENCV_LIB_INSTALL_PATH       	${OpenCV_BINARY_DIR}lib/)
	if (WIN32)
  		set(OPENCV_WORLD_INSTALL_PATH   "${OPENCV_BIN_INSTALL_PATH}opencv_world450.dll")
	else()
  		set(OPENCV_WORLD_INSTALL_PATH 	"${OPENCV_LIB_INSTALL_PATH}libopencv_world.so")
	endif()

	add_subdirectory(opencv-4.5.0)
	include_directories(${OPENCV_INCLUDE_INSTALL_PATH})
	link_directories(${OPENCV_LIB_INSTALL_PATH})
else()
	include_directories(${OpenCV_INCLUDE_DIRS})
	get_target_property(OPENCV_WORLD_INSTALL_PATH opencv_world LOCATION_RELEASE)
endif()

set(Boost_USE_STATIC_LIBS 			ON)
find_package(Boost COMPONENTS filesystem regex program_options)
if(NOT Boost_FOUND)
	message(STATUS "Boost wasn't found. Installation of boost-1.67.0 started...")	
	add_subdirectory(boost-1.67.0)
else()
	include_directories(${Boost_INCLUDE_DIRS})
endif()

set(DETECTOR_BINARY_DIR 			${CMAKE_BINARY_DIR}/../detector/)
add_subdirectory(detector_lib)
add_subdirectory(detector)

add_subdirectory(gtest-1.10.0)
include_directories(gtest-1.10.0/googletest/include/)

add_subdirectory(tests)
if(MSVC)
	if("${MSVC_RUNTIME}" STREQUAL "")
		set(MSVC_RUNTIME "static")
    	endif()

    	set(variables
      		CMAKE_C_FLAGS_DEBUG
      		CMAKE_C_FLAGS_MINSIZEREL
      		CMAKE_C_FLAGS_RELEASE
      		CMAKE_C_FLAGS_RELWITHDEBINFO
      		CMAKE_CXX_FLAGS_DEBUG
      		CMAKE_CXX_FLAGS_MINSIZEREL
      		CMAKE_CXX_FLAGS_RELEASE
      		CMAKE_CXX_FLAGS_RELWITHDEBINFO
    	)

    	if(${MSVC_RUNTIME} STREQUAL "static")
      		message(STATUS "MSVC -> forcing use of statically-linked runtime.")
      		foreach(variable ${variables})
        		if(${variable} MATCHES "/MD")
          			string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
        		endif()
      		endforeach()
    	else()
      		message(STATUS "MSVC -> forcing use of dynamically-linked runtime.")
      		foreach(variable ${variables})
        		if(${variable} MATCHES "/MT")
          			string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
        		endif()
      		endforeach()
    	endif()
endif()

include_directories(include/)
include_directories(../detector/include/)
add_executable(tests src/main.cpp src/testLib.cpp ../detector/src/FaceDetectorDLL.cpp)

add_dependencies(tests detector_lib)

target_link_libraries(tests gtest)
target_link_libraries(tests opencv_world)

set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY 	 ${DETECTOR_BINARY_DIR})
set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${DETECTOR_BINARY_DIR})
set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${DETECTOR_BINARY_DIR})
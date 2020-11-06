cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD         11)
set(CMAKE_INSTALL_PREFIX       ${CMAKE_BINARY_DIR}/install/ CACHE PATH "Install prefix" FORCE)

project(FaceDetector)
add_subdirectory(source)
cmake_minimum_required(VERSION 3.26)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/fabEngine/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(FabEngine)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(./fabEngine)
  
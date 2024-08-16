cmake_minimum_required(VERSION 3.10)
project(CUDA_NPP_Image_Processing)

find_package(CUDA REQUIRED)

include_directories(${CUDA_INCLUDE_DIRS} include)

cuda_add_executable(main src/main.cpp src/image_processing.cpp)
target_link_libraries(main ${CUDA_LIBRARIES} nppc nppi)
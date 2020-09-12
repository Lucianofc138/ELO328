cmake_minimum_required(VERSION 2.8)
project( GAMMA )
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
find_package( OpenCV REQUIRED )

add_executable( GAMMA main.cpp
                src/cmdArgsTools.cpp
                src/imageProcTools.cpp)
target_include_directories( GAMMA PRIVATE include)
target_link_libraries( GAMMA ${OpenCV_LIBS} )

 add_executable( TEST_TIME test/main.cpp
                           src/imageProcTools.cpp)
 target_include_directories( TEST_TIME PRIVATE include)
 target_link_libraries( TEST_TIME ${OpenCV_LIBS} )
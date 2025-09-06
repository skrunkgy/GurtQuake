cmake_minimum_required(VERSION 3.10)
project(gquake)

add_executable(gquake src/main.cpp src/app.cpp src/mesh.cpp src/shader.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories  (gquake PUBLIC
                            "./include"
                            )

set(HEADER_DIRS "./include")
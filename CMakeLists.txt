cmake_minimum_required(VERSION 3.13)
project(gquake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories  ("include")
link_directories("lib")

add_executable(gquake src/main.cpp src/app.cpp src/mesh.cpp src/shader.cpp)

# Set SDL3 libraries

target_link_libraries(gquake ${CMAKE_CXX_STANDARD_LIBRARIES})

add_compile_definitions(GLEW_STATIC)
target_link_libraries(gquake glew32 opengl32)
target_link_libraries(gquake SDL3 winmm imm32 version setupapi dinput8)
cmake_minimum_required(VERSION 3.13)
project(gquake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Make this autonomous
add_executable(gquake src/main.cpp src/app.cpp src/mesh.cpp src/shader.cpp src/gqobject.cpp)

# Other libraries and headers
target_include_directories(gquake PRIVATE "include")
target_include_directories(gquake PRIVATE "/usr/include")
link_directories("lib")

# Set SDL3 libraries

target_link_libraries(gquake ${CMAKE_CXX_STANDARD_LIBRARIES})

# Note: Add windows specific instructions here somewhere

add_compile_definitions(GLEW_STATIC)
target_link_libraries(gquake GLEW GL)
target_link_libraries(gquake SDL3)
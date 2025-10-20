cmake_minimum_required(VERSION 3.13)
project(gquake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Make this autonomous
add_executable(gquake src/main.cpp src/app.cpp src/mesh.cpp src/shader.cpp src/gqobject.cpp)

# Other libraries and headers
target_include_directories(gquake PRIVATE "include")
target_include_directories(gquake PRIVATE "/usr/include")
target_include_directories(gquake PRIVATE "/usr/lib")
link_directories("lib")

# Set SDL3 libraries

target_link_libraries(gquake ${CMAKE_CXX_STANDARD_LIBRARIES})

add_compile_definitions(GLEW_STATIC)
if (WIN32)
    target_link_libraries(gquake glew32 opengl32)
else ()
    target_link_libraries(gquake GLEW GL) # Linux
endif (WIN32)

target_link_libraries(gquake SDL3)
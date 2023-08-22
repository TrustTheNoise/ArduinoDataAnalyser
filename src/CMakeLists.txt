cmake_minimum_required(VERSION 3.2)
project(TaskImGui LANGUAGES CXX)
cmake_policy(SET CMP0072 NEW)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../lib lib)
add_executable(TaskImGui main.cpp)

# Linking to the imgui library
target_link_libraries(TaskImGui PRIVATE imgui)

# Add directory of headers
target_include_directories(TaskImGui PRIVATE ../headers)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_link_libraries(TaskImGui
                        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../libglfw3.a)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  find_package(glfw3 REQUIRED)
endif()

# Finding OpenGL and set variable OPENGL_INCLUDE_DIR with directory of OpenGL
find_package(OpenGL REQUIRED)

target_include_directories(TaskImGui PRIVATE ${OPENGL_INCLUDE_DIR})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_link_libraries(TaskImGui PRIVATE OpenGL::GL)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_link_libraries(TaskImGui PRIVATE glfw OpenGL::GL)
endif()

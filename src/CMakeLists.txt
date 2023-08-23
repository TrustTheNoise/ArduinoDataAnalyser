cmake_minimum_required(VERSION 3.10)

project(TaskImGui LANGUAGES CXX)
cmake_policy(SET CMP0072 NEW)

# Adding directories where our libraries are located
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ImGui ImGui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../CoreLibs CoreLibs)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib lib)

# Changing the names for our executing file That is, if you want to change the
# name, just change the "TemplateImGui" in this line
set(target_name ArduinoDataAnalyser)

# Creating the actual executable file
add_executable(${target_name} main.cpp)

# Linking to executable file libraries
target_link_libraries(${target_name} PRIVATE imgui)
target_link_libraries(${target_name} PRIVATE MyApp)
target_link_libraries(${target_name} PRIVATE CoreLibs)

# Add directory of headers
target_include_directories(${target_name} PRIVATE ../ImGui/)
target_include_directories(${target_name} PRIVATE ./lib/)

# Adding the glfw3 library depending on the platform
target_link_libraries(${target_name}
                      PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../libglfw3.a)

# Finding OpenGL and set variable OPENGL_INCLUDE_DIR with directory of OpenGL
find_package(OpenGL REQUIRED)
# Adding OpenGL library
target_include_directories(${target_name} PRIVATE ${OPENGL_INCLUDE_DIR})

target_link_libraries(${target_name} PRIVATE OpenGL::GL)

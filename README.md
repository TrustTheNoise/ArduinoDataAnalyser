# ArduinoDataAnalyser

## Base
This is a program designed to receive data from an arduino and display it on the screen, then save it to a text file.
The project was created using ImGui on OpenGL glfw3, the SerialPort library was also used to work with arduino data.

Cmake is used for the building.

## Build
The directory with the assembly is src/ the main one is located there CMakeLists.txt . Usually a build directory is created for the build.
With each build via cmake, write `cmake -G Ninja <path to src/>` in the folder where you want to build the project

## What you need
The directory with the assembly is src/ the main one is located there CMakeLists.txt . Usually a build directory is created for the build.
With each build via cmake, write `cmake -G Ninja <path to src/>` in the folder where you want to build the project

## Working with program
In src/main, you need to select your COM port with arduino in the port variable. Then assemble the project. The window will immediately begin to output data from the arduino, you can stop or continue collecting data from the arduino, you can also use the Save button to start selecting the name of the text file.

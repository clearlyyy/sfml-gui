# This is for Linux builds.
# Make sure you have the "sfml" package installed on your system.

cmake_minimum_required(VERSION 3.16)
project(sfml-gui-testbuild LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML 3 
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/sfml-gui/sf_widget.cpp
    src/sfml-gui/gui.cpp
)

# Link SFML 3 targets 
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)

# Add OpenGL 
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)


































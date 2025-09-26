cmake_minimum_required(VERSION 3.16)
project(sfml-gui-testbuild LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add SFML include path
include_directories("C:/Libraries/SFML/include")

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/sfml-gui/sf_widget.cpp
    src/sfml-gui/gui.cpp)

# Link SFML 3 import libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    "C:/Libraries/SFML/lib/libsfml-graphics.a"
    "C:/Libraries/SFML/lib/libsfml-window.a"
    "C:/Libraries/SFML/lib/libsfml-system.a"
    opengl32
)

# Copy DLLs to build folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Libraries/SFML/bin/sfml-graphics-3.dll"
        "C:/Libraries/SFML/bin/sfml-window-3.dll"
        "C:/Libraries/SFML/bin/sfml-system-3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)



































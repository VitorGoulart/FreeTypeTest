cmake_minimum_required(VERSION 3.27)
project(learnOpenGL)

set(CMAKE_CXX_STANDARD 20)
set(USER_HOME_DIRECTORY $ENV{USERPROFILE})

include_directories(Dependencies/include)
link_directories(Dependencies/lib)

add_executable(learnOpenGL main.cpp
        glad.c
        shader.h
        Sprites/Sprite.h
        stb_image.cpp
        Sprites/Sprite.cpp
        shader.cpp
        Sprites/Player.cpp
        Sprites/Player.h
        GameValues.h
        Sprites/Fish.cpp
        Sprites/Fish.h
        Sprites/Trash.cpp
        Sprites/Trash.h
        Sprites/BackgroundLayer.cpp
        Sprites/BackgroundLayer.h
        Text.cpp
        Text.h
        TextRenderer.cpp
        TextRenderer.h
)
target_link_libraries(learnOpenGL glfw3)
target_link_libraries(learnOpenGL freetype)
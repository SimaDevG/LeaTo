cmake_minimum_required(VERSION 3.1)

project(LeaTo LANGUAGES CXX)

add_executable(LeaTo
    src/main.cpp
    src/button.cpp
    src/block.cpp
    src/entity.cpp
    src/event.cpp
    src/func.cpp
    src/main.cpp
    src/mouse.cpp
    src/player.cpp
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(LeaTo
    PUBLIC include/
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2IMAGE_INCLUDE_DIRS}
)

if(WIN32)
    target_link_libraries(LeaTo PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image mingw32)
else()
    target_link_libraries(LeaTo PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
endif()
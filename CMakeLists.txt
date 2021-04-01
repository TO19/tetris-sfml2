cmake_minimum_required(VERSION 2.8.12)
project(IDVCPP4)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")
add_definitions(-std=c++11)
file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Assets/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/Assets/)

include_directories(src src/Managers src/Assets src/Factories src/Entities src/Observers src/Entities/Abstract src/Interfaces)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME}
               src/main.cpp
               src/Entities/Abstract/AbstractEntity.cpp
               src/Entities/Movable.cpp
               src/Entities/Scene.cpp
               src/Factories/ShapeFactory.cpp
               src/Managers/TimeManager.cpp
               src/Entities/ShapeEntity.cpp
               src/Entities/PlayableArea.cpp
               src/Entities/BlockEntity.cpp
               src/Observers/RowObserver.cpp
               src/Observers/PlaceScoreObserver.cpp
               src/Managers/AssetsManager.cpp
               src/Managers/TxtFileManager.cpp
               src/Managers/SoundManager.cpp
               src/Entities/State.cpp
               src/Entities/Menu.cpp
               src/Managers/AssetsManager.cpp
               src/Entities/BlockEntity.cpp)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
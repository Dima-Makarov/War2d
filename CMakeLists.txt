cmake_minimum_required(VERSION 3.17)
project(War2d)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON) # Enable Qt MOC compiler
set(CMAKE_AUTORCC ON) # Enable Qt resources compiler
set(CMAKE_AUTOUIC ON) # Enable Qt UI compiler

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\")")
endif ()

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Widgets Gui)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Widgets Qt5::Gui)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -O0")

set(SOURCES
        main.cpp
        View/view.cpp
        Model/model.cpp
        Model/player.cpp
        Model/weapon_handler.cpp
        Controller/controller.cpp
        GameObjects/bullet.cpp
        GameObjects/game_object.cpp
        GameObjects/plane.cpp
        GameObjects/ship.cpp
        GameObjects/tank.cpp
        GameObjects/vehicle.cpp
        Utils/pixmap_loader.cpp
        Utils/vec2f.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

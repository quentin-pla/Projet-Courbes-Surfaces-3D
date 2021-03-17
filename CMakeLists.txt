cmake_minimum_required(VERSION 3.17)
project(visuCourbe)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(QT_USE_QTGUI TRUE)
set(QT_USE_QTXML TRUE)

# Localisation de Qt
set(Qt5_DIR "~/Qt/5.15.2/clang_64/lib/cmake/Qt5")

# Récupération des modules Qt
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(visuCourbe
        resources.qrc
        main.cpp
        mainwindow.cpp
        myopenglwidget.cpp
        point.cpp
        segment.cpp
        globject.cpp
        discretisation.cpp
        courbeparametrique.cpp
        courbebezier.cpp
        carreaubezier.cpp)

include_directories(. ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

target_link_libraries(visuCourbe ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

# Liaison des modules à l'exécutable
target_link_libraries(visuCourbe Qt5::Core Qt5::Widgets)
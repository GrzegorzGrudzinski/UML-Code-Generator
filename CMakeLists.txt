cmake_minimum_required(VERSION 3.16)

project(UML-Code-Generator VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

# --- PLIKI ŹRÓDŁOWE (BACKEND) ---
set(CORE_SOURCES
    src/Core/UmlModel/UmlClass.cpp
    src/Core/UmlModel/UmlAttribute.cpp
    src/Core/UmlModel/UmlMethod.cpp
    src/Core/Refiner/UmlRefiner.cpp
    src/Core/CodeGenerator/CodeGenerator.cpp
)

# --- PLIKI ŹRÓDŁOWE (GUI) ---
set(GUI_SOURCES
    src/GUI/mainwindow.cpp
    src/GUI/mainwindow.ui
    src/GUI/Graphics/UmlClassItem.cpp  
)

# Główny plik startowy
set(MAIN_SOURCE src/main.cpp)

add_executable(${PROJECT_NAME}  # WIN32 
    ${MAIN_SOURCE}
    ${CORE_SOURCES}
    ${GUI_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src/Core/UmlModel
    src/Core/Refiner

    src/Core/CodeGenerator
    src/Core/CodeGenerator/generators

    src/GUI
    src/GUI/Graphics
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
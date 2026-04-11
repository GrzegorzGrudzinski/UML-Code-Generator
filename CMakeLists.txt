cmake_minimum_required(VERSION 3.10.0)

project(UML-Code-Generator VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

include_directories(
    src/Core/UmlModel
    src/Core/Refiner
    src/Core/CodeGenerator/generators
    src/Core/CodeGenerator
    )

set(HEADERS
    src/Core/UmlModel/UmlClass.hpp
    src/Core/UmlModel/UmlAttribute.hpp
    src/Core/UmlModel/UmlMethod.hpp
    src/Core/Refiner/UmlRefiner.hpp
    src/Core/CodeGenerator/CodeGenerator.hpp
    src/Core/CodeGenerator/generators/CppGenerator.hpp
    src/Core/CodeGenerator/generators/PythonGenerator.hpp
)

set(SOURCES
    src/main.cpp
    src/Core/UmlModel/UmlClass.cpp
    src/Core/UmlModel/UmlAttribute.cpp
    src/Core/UmlModel/UmlMethod.cpp
    src/Core/Refiner/UmlRefiner.cpp
    src/Core/CodeGenerator/CodeGenerator.cpp
    # src/Core/CodeGenerator/generators/CppGenerator.cpp
    # src/transformations/TransformationEngine.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# --- SEKCJA NA PRZYSZŁOŚĆ (GUI - Qt) ---
# Gdy będziesz gotowy na okienka, odkomentujesz te linijki:
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)
# find_package(Qt6 COMPONENTS Widgets REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
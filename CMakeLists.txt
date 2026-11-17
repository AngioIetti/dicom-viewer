cmake_minimum_required(VERSION 3.16)

project(dicom-viewer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.4 REQUIRED COMPONENTS Widgets)
find_package(DCMTK CONFIG REQUIRED)

qt_standard_project_setup()

add_subdirectory(src)
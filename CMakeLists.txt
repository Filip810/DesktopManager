
cmake_minimum_required(VERSION 3.10)


project(DesktopMenager)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



include_directories(include)


set(SOURCES
    src/main.cpp
    src/operations/FileSorter.cpp
    src/operations/Operations.cpp
    src/operations/FileCleaner.cpp
    src/operations/SizeFileSorter.cpp
    src/operations/ExtensionFileCleaner.cpp
    src/operations/DateFileSorter.cpp
    src/operations/DateFileCleaner.cpp


)


add_executable(my_program ${SOURCES})


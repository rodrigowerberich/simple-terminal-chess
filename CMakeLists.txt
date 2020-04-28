CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)

#set the project name
PROJECT(Chess VERSION 1.0)

# specify the c++ standart
SET(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
SET(CMAKE_EXE_LINKER_FLAGS "-static -std=c++17 -Wall -fPIC")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

FILE(GLOB MY_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cc")
MESSAGE("MY_SOURCES: ${MY_SOURCES}")

#add the executable
ADD_EXECUTABLE(chess ${MY_SOURCES})

target_include_directories(chess PUBLIC 
                            ${PROJECT_SOURCE_DIR}/src
                           )
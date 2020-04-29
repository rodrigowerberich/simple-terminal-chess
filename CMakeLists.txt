CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)

#set the project name
PROJECT(Chess VERSION 1.0)

# specify the c++ standard
SET(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
SET(CMAKE_EXE_LINKER_FLAGS "-static -std=c++17 -Wall -fPIC")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

FILE(GLOB MY_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cc")
MESSAGE("MY_SOURCES: ${MY_SOURCES}")

#add the executable
ADD_EXECUTABLE(chess ${MY_SOURCES})
ADD_EXECUTABLE(printer_test  "${CMAKE_SOURCE_DIR}/tst/Printer/Printer_tester.cc"
                             "${CMAKE_SOURCE_DIR}/src/Printer.cc")

ADD_EXECUTABLE(parser_test  "${CMAKE_SOURCE_DIR}/tst/Parser/Parser_tester.cc"
                            "${CMAKE_SOURCE_DIR}/src/Parser.cc")
ADD_EXECUTABLE(command_quit_test    "${CMAKE_SOURCE_DIR}/tst/CommandQuit/CommandQuit_tester.cc"
                                    "${CMAKE_SOURCE_DIR}/src/CommandQuit.cc")
        

target_include_directories(chess PUBLIC 
                            ${PROJECT_SOURCE_DIR}/src
                           )

target_include_directories(printer_test PUBLIC 
                            ${PROJECT_SOURCE_DIR}/src
                           )

target_include_directories(parser_test PUBLIC 
                            ${PROJECT_SOURCE_DIR}/src
                           )

target_include_directories(command_quit_test PUBLIC 
                            ${PROJECT_SOURCE_DIR}/src
                           )
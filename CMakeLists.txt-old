CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)

#set the project name
PROJECT(Chess VERSION 1.0)

# specify the c++ standard
SET(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
SET(CMAKE_EXE_LINKER_FLAGS "-static -std=c++17 -Wall -fPIC")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

FILE(GLOB MY_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cc")
MESSAGE("MY_SOURCES: ${MY_SOURCES}")

# Main executable
ADD_EXECUTABLE(chess ${MY_SOURCES})

target_include_directories(chess PUBLIC 
                            ${PROJECT_SOURCE_DIR}/src
                           )


# Autotesters
# Tester Printer
ADD_EXECUTABLE(printer_test  "${CMAKE_SOURCE_DIR}/tst/Printer/Printer_tester.cc"
                             "${CMAKE_SOURCE_DIR}/src/Printer.cc")

target_include_directories(printer_test PUBLIC 
                            ${PROJECT_SOURCE_DIR}/src
                           )


# Tester Printer
ADD_EXECUTABLE(parser_test  "${CMAKE_SOURCE_DIR}/tst/Parser/Parser_tester.cc"
                            "${CMAKE_SOURCE_DIR}/src/Parser.cc")

target_include_directories(parser_test PUBLIC 
                            ${PROJECT_SOURCE_DIR}/src
                           )

# Tester BoardPosition
ADD_EXECUTABLE(board_position_test  "${CMAKE_SOURCE_DIR}/tst/BoardPosition/BoardPosition_tester.cc"
                            "${CMAKE_SOURCE_DIR}/src/BoardPosition.cc")

target_include_directories(board_position_test PUBLIC 
                            ${PROJECT_SOURCE_DIR}/src
                           )                           
# Tester Piece
ADD_EXECUTABLE(piece_test  "${CMAKE_SOURCE_DIR}/tst/Piece/Piece_tester.cc"
                            "${CMAKE_SOURCE_DIR}/src/BoardPosition.cc"
                            "${CMAKE_SOURCE_DIR}/src/Piece.cc")

target_include_directories(piece_test PUBLIC 
                            ${PROJECT_SOURCE_DIR}/src
                           )                           


# Tester CommandQuit

ADD_EXECUTABLE(command_quit_test    "${CMAKE_SOURCE_DIR}/tst/CommandQuit/CommandQuit_tester.cc"
                                    "${CMAKE_SOURCE_DIR}/src/CommandQuit.cc")
        
target_include_directories(command_quit_test PUBLIC 
                            ${PROJECT_SOURCE_DIR}/src
                           






)
cmake_minimum_required(VERSION 4.0)
project(Advent_Of_Code_2025)

set(CMAKE_CXX_STANDARD 23)

set(HEADER_FILES
        source/Common/FileReader.h
        source/Common/IDayProcessor.h
        source/Common/StringUtils.h
        source/Common/Globals.h
)

set(SOURCE_FILES
        source/Common/FileReader.cpp
        source/Common/StringUtils.cpp
)

set(DAY_PROCESSORS
        source/Day_1/Day1Processor.h
        source/Day_1/Day1Processor.cpp
        source/Day_2/Day2Processor.h
        source/Day_2/Day2Processor.cpp
        source/Day_3/Day3Processor.cpp
        source/Day_3/Day3Processor.hpp
        source/Day_4/Day4Processor.cpp
        source/Day_4/Day4Processor.hpp
)

set(ALL_FILES ${HEADER_FILES} ${SOURCE_FILES} ${DAY_PROCESSORS})

add_executable(Advent_Of_Code_2025 source/main.cpp ${ALL_FILES})

add_custom_command(
                    TARGET Advent_Of_Code_2025 PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/input
                    $<TARGET_FILE_DIR:Advent_Of_Code_2025>/input
                    COMMENT "Copying input files to build directory"
)

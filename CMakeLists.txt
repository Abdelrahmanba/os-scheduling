cmake_minimum_required(VERSION 3.19)
project(Scheduling_Algorithms_Testbench)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES
        src/helperFunctions.cpp
        src/metrics.cpp
        src/process.cpp
        src/schedulingFunctions.cpp
        )

set(Headers
        include/helperFunctions.h
        include/metrics.h
        include/process.h
        include/schedulingFunctions.h
        )

add_executable(Scheduling_Algorithms_Testbench main.cpp ${SOURCES} ${Headers})
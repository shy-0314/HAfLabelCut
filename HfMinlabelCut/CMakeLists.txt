cmake_minimum_required(VERSION 3.26)
project(12_6)

set(CMAKE_CXX_STANDARD 17)

add_executable(12_6 main.cpp
        GraphAdjMat.h
        ObjArrayList.h
        LinkQueue.h
        GraphAdjMat.cpp
        GraphAdjMat_Test.cpp
        tools.h
        tools.cpp
)

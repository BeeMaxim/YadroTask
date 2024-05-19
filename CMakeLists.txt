cmake_minimum_required(VERSION 3.16)
project(yadro_task)

set(CMAKE_CXX_STANDARD 20)

add_executable(main
        main.cpp
        Time.cpp
        utils.cpp
        EventProcessor.cpp
        StateInfo.cpp
        Station.cpp
)
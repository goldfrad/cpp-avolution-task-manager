cmake_minimum_required(VERSION 3.10)
project(TaskManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(task_manager
    main.cpp
)
# mavlink-interface/CMakeLists.txt

cmake_minimum_required(VERSION 3.15)

project(mavlink-interface VERSION 0.1.0
        DESCRIPTION "mavlink-interface library"
        LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_sources(${PROJECT_NAME}
    PUBLIC
        msg_queue.h
        multithreaded_interface.h
        position_controller.h
        serial_port.h
    PRIVATE
        multithreaded_interface.cpp
        position_controller.cpp
        serial_port.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ./ mavlink_c_library_v1)

include_directories(mavlink_c_library_v1)



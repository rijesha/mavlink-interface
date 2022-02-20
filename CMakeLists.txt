# mavlink-interface/CMakeLists.txt

cmake_minimum_required(VERSION 3.15)

project(mavlink-interface VERSION 0.1.0
        DESCRIPTION "mavlink-interface library"
        LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_sources(${PROJECT_NAME}
    PUBLIC
        include/multithreaded_interface.h
        include/position_control_helper.h
        include/serial_port.h
        include/udp_device.h
    PRIVATE
        include/msg_queue.h
        src/multithreaded_interface.cpp
        src/serial_port.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include mavlink_c_library_v2/ardupilotmega)

include_directories(mavlink_c_library_v2)



cmake_minimum_required(VERSION 3.0)
project(mavlink_interface)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -DSTANDALONE")

set(SOURCE_FILES
        main.cpp
        msg_queue.h
        multithreaded_interface.cpp
        multithreaded_interface.h
        position_controller.cpp
        position_controller.h
        serial_port.cpp
        serial_port.h)

add_executable(mavlink_interface ${SOURCE_FILES})
include_directories(mavlink_c_library_v1)
target_link_libraries(mavlink_interface pthread)

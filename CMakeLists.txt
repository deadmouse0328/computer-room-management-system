cmake_minimum_required(VERSION 3.27)
project(machine_room_reservation_system)

set(CMAKE_CXX_STANDARD 17)

add_executable(machine_room_reservation_system main.cpp
        identity.h
        student.h
        student.cpp
        teacher.cpp
        teacher.h
        manager.cpp
        manager.h
        globalFile.h
        computerRoom.h
        orderFile.cpp
        orderFile.h)

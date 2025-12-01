cmake_minimum_required(VERSION 3.0)
project(RUHungry C)

set(CMAKE_C_STANDARD 11)

add_executable(RUHungry main.c
        menu.c
        menu.h
        customer.h
        customer.c
        order.c
        order.h)

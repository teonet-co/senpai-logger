cmake_minimum_required(VERSION 3.16)
project(senpai_logger C)

set(CMAKE_C_STANDARD 11)

add_library(senpai_logger senpai-logger.c senpai-logger.h)
cmake_minimum_required(VERSION 3.27)

project("ShinyHash")

add_library(base src/base.cpp)
add_library(sha src/sha.cpp)
add_library(md src/md.cpp)
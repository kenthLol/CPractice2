cmake_minimum_required(VERSION 3.24)

project(CPractice2 C)

add_executable(${PROJECT_NAME} Main.c)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)
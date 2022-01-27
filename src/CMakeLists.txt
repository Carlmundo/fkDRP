cmake_minimum_required(VERSION 3.0.0)
project(W2-DRP VERSION 1.0)

include(CTest)
enable_testing()

add_library(W2-DRP main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

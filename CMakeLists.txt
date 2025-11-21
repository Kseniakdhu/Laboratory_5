cmake_minimum_required(VERSION 3.30) 

project(Container)

set(CMAKE_CXX_STANDARD 20) 

set(BINARY ${CMAKE_PROJECT_NAME})

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${INCLUDE_DIR})

add_library(${BINARY}_lib STATIC 
    ${SOURCE_DIR}/Fixed_Block_Memory_Resource.cpp
)

add_executable(main ${SOURCE_DIR}/main.cpp)

target_link_libraries(main ${BINARY}_lib)

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

enable_testing()
add_subdirectory(test)

cmake_minimum_required(VERSION 3.10)
project(StudentsProject C)

set(CMAKE_C_STANDARD 99)

option(STATIC "Build static library" ON)

set(SOURCES
    students_io.c
    students_search.c
)

if(STATIC)
    add_library(students STATIC ${SOURCES})
else()
    add_library(students SHARED ${SOURCES})
endif()

add_executable(main_program main.c)

target_link_libraries(main_program students)

if(NOT STATIC)
    set_target_properties(main_program PROPERTIES
        BUILD_RPATH "$ORIGIN"
    )
endif()
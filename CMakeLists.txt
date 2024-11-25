cmake_minimum_required(VERSION 3.21)

project(LQVM
        LANGUAGES CXX)

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source build is forbidden")
endif()

find_package(fmt REQUIRED)
find_package(CLI11 REQUIRED)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_executable(lqvm
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/lqvm.cpp
    ${SOURCE_DIR}/function.cpp
)

set_target_properties(lqvm PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(lqvm
    PRIVATE ${INCLUDE_DIR}
)

target_link_libraries(lqvm
    PRIVATE CLI11::CLI11 fmt::fmt
)

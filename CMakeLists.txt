cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(tchjs)

# Node-cmake
include(NodeJS.cmake)
nodejs_init()

file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/csrc/*.cc" "${PROJECT_SOURCE_DIR}/csrc/*.h")
add_nodejs_module(${PROJECT_NAME} ${SRC_FILES})

# Look for shared libs in the same directory
IF (UNIX)
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-rpath,$ORIGIN")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,$ORIGIN")
ENDIF(UNIX)

# Include N-API wrappers
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/node_modules/node-addon-api")

find_package(Torch PATHS "./libtorch/" REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)
target_link_libraries(${PROJECT_NAME} "${TORCH_LIBRARIES}")

project(pwatch)
cmake_minimum_required(VERSION 2.8)

set(RUNTIME_DIR "bin")

if (${CMAKE_SYSTEM_NAME} EQUAL "Linux") 
 add_definitions(-DLINUX_BUILD) 
endif (${CMAKE_SYSTEM_NAME} EQUAL "Linux") 
 

include_directories(src/atexit)

add_subdirectory(src/atexit build/atexit)
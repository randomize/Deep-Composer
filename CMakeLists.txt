cmake_minimum_required(VERSION 2.8)

# Globals
project(threads-test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2  ")

message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Threads)
find_package(OpenEXR REQUIRED)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package( Boost 1.40 COMPONENTS thread system REQUIRED )
message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")

include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ${OPENEXR_INCLUDE_PATHS} )
# Compiling
set(SOURCES main.cpp Image.cpp DepthImage.cpp)
add_executable(threads ${SOURCES})
target_link_libraries(threads  ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} )
target_link_libraries(threads  ${OPENEXR_LIBRARIES})


cmake_minimum_required(VERSION 2.8)

# Globals
project(threads-test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2  ")

message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

find_package(Threads)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package( Boost 1.40 COMPONENTS thread system REQUIRED )
message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")

include_directories( ${Boost_INCLUDE_DIR} )
# Compiling
set(SOURCES main.cpp tinyexr/tinyexr.cc )
add_executable(threads ${SOURCES})
target_link_libraries(threads  ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} )


cmake_minimum_required(VERSION 2.8)



# Globals =============================

project(deep-compose)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic ")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic -fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g0 -msse4.2  ")

message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)




# Libs and tools =====================

# C++11 threads (just in case OpenMP not enough)
find_package(Threads)

# OpenEXR allows to read and write exr files
find_package(OpenEXR REQUIRED)
include_directories( ${OPENEXR_INCLUDE_PATHS} )

# OpenMP to be parallel
# find_package(OpenMP)
# if (OPENMP_FOUND)
#     set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#     set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# endif()

# Libpng
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

# Boost, because it rocks
# set(Boost_USE_STATIC_LIBS        ON) # only find static libs
# set(Boost_USE_MULTITHREADED      ON)
# set(Boost_USE_STATIC_RUNTIME    OFF)
# find_package( Boost 1.40 COMPONENTS thread system REQUIRED )
# message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
# message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
# message(status "** Boost Libraries: ${Boost_LIBRARIES}")
# include_directories( ${Boost_INCLUDE_DIR} )




# Compiling =======================

set(SOURCES main.cpp Image.cpp DepthImage.cpp)
add_executable(dcompose ${SOURCES})
target_link_libraries(dcompose  ${CMAKE_THREAD_LIBS_INIT})
# target_link_libraries(dcompose  ${Boost_LIBRARIES})
target_link_libraries(dcompose  ${OPENEXR_LIBRARIES})
target_link_libraries(dcompose ${PNG_LIBRARY})


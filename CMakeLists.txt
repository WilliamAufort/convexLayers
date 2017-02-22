PROJECT(experiments)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# We need Boost Program Options library to test
SET(Boost_USE_STATIC_LIBS   ON)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
SET(Boost_FOUND FALSE)
FIND_PACKAGE(Boost 1.46.0 REQUIRED COMPONENTS program_options)
if ( Boost_FOUND )
  message(STATUS "Boost and boost_program_options found.")
  include_directories( ${Boost_INCLUDE_DIRS} )
endif( Boost_FOUND )

# DGtal requirement

FIND_PACKAGE(DGtal REQUIRED)
INCLUDE_DIRECTORIES(${DGTAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${DGTAL_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

# ConvexLayers
add_executable(convexLayers src/convexLayers.cpp)
target_link_libraries(convexLayers ${DGTAL_LIBRARIES})

# Polynomials
add_executable(polynomial src/polynomial.cpp)

# Program
add_executable(program src/program.cpp src/parserArguments.cpp src/convexHulls.cpp src/minkowski.cpp)
target_link_libraries(program ${DGTAL_LIBRARIES})

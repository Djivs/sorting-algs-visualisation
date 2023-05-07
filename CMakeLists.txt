cmake_minimum_required(VERSION 3.5)

project(sorting-algs-visualisation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        polygon.h polygon.cpp
        engine.h engine.cpp
)
add_executable(sorting-algs-visualisation  ${PROJECT_SOURCES})

target_include_directories(sorting-algs-visualisation 
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )

set_target_properties(sorting-algs-visualisation
  PROPERTIES
      INSTALL_RPATH
        "${CMAKE_INSTALL_PREFIX}/lib"
  )

target_link_libraries(sorting-algs-visualisation sfml-graphics sfml-audio)

install(TARGETS sorting-algs-visualisation DESTINATION bin)
cmake_minimum_required(VERSION 3.11)

project(short_vector VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_SHORT_VECTOR_TESTING "Build the tests for short_vector" ON)
option(INSTALL_SHORT_VECTOR "Install the short vector library" OFF)

option(AUTO "Build short vectors using compiler optimizations" ON)
option(SSE "Build short vectors for SSE" ON)
option(AVX2 "Build short vectors for AVX2" ON)

list(APPEND CMAKE_MODULE_PATH ${short_vector_SOURCE_DIR}/cmake_modules)

if(INSTALL_SHORT_VECTOR)
  include(GNUInstallDirs)
  set(short_vector_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
  set(short_vector_INSTALL_CONFDIR ${CMAKE_INSTALL_LIBDIR}/cmake/short_vector)
endif()

add_subdirectory(short_vector)

if(INSTALL_SHORT_VECTOR)
  install(
    EXPORT short_vector_targets
    FILE short_vector_targets.cmake
    NAMESPACE short_vector::
    DESTINATION ${short_vector_INSTALL_CONFDIR})
endif()


if(BUILD_SHORT_VECTOR_TESTING)
  enable_testing()
  add_subdirectory(short_vector_testing)
endif()

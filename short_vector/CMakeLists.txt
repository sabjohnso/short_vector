
add_library(short_vector INTERFACE)
target_include_directories(short_vector
  INTERFACE
  $<BUILD_INTERFACE:${short_vector_SOURCE_DIR}>
  $<BUILD_INTERFACE:${short_vector_BINARY_DIR}>)

add_library(short_vector::short_vector ALIAS short_vector)

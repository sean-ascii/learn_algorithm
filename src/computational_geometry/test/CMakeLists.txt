add_executable(basic_geometry_test
  basic_geometry_test.cpp
  ../basic_geometry.cpp
)
target_link_libraries(basic_geometry_test
  ${GTEST_BOTH_LIBRARIES}
  pthread
)
add_test(basic_geometry_test
  ${CMAKE_CURRENT_BINARY_DIR}/basic_geometry_test
)
add_executable(sort_test
  sort_test.cpp
  ../sort.cpp
)
target_link_libraries(sort_test
  ${GTEST_BOTH_LIBRARIES}
  pthread
)
add_test(sort_test
  ${CMAKE_CURRENT_BINARY_DIR}/sort_test
)
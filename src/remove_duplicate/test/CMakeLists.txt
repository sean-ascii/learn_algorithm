add_executable(remove_duplicate_test
  remove_duplicate_test.cpp
  ../remove_duplicate.cpp
)

target_link_libraries(remove_duplicate_test
  ${GTEST_BOTH_LIBRARIES}
  pthread
)

add_test(remove_duplicate_test
  ${CMAKE_CURRENT_BINARY_DIR}/remove_duplicate_test
)
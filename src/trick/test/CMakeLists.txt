add_executable(trick_test
  trick_test.cpp
  ../trick.cpp
)
target_link_libraries(trick_test
  ${GTEST_BOTH_LIBRARIES}
  pthread
)
add_test(trick_test
  ${CMAKE_CURRENT_BINARY_DIR}/trick_test
)
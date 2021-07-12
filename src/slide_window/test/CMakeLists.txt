add_executable(slide_window_test
  slide_window_test.cpp
  ../min_substring.cpp
  ../check_inclusion.cpp
  ../longest_unrepeated_substring.cpp
)
target_link_libraries(slide_window_test
  ${GTEST_BOTH_LIBRARIES}
  pthread
)

add_test(slide_window_test
  ${CMAKE_CURRENT_BINARY_DIR}/slide_window_test
)
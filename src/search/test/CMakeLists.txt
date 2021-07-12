add_executable(search_test
  search_test.cpp
  ../binary_search.cpp
  ../bfs.cpp
)

target_link_libraries(search_test
  ${GTEST_BOTH_LIBRARIES}
  pthread
)

add_test(search_test
  ${CMAKE_CURRENT_BINARY_DIR}/search_test
)
add_executable(data_structure_test
  data_structure_test.cpp
  ../LRU.cpp
  ../random_set.cpp
  ../reverse_list.cpp
  ../binary_tree.cpp
  ../LCA.cpp
  ../union_find_set.cpp
  ../LFU.cpp
  ../median_finder.cpp
  ../monotonic_stack.cpp
  ../monotonic_queue.cpp
  ../binary_heap.cpp
  ../graph.cpp
)

target_link_libraries(data_structure_test
  ${GTEST_BOTH_LIBRARIES}
  pthread
)

add_test(data_structure_test
  ${CMAKE_CURRENT_BINARY_DIR}/data_structure_test
)
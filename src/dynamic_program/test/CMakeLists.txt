add_executable(dynamic_program_test
  dynamic_program_test.cpp
  ../coin_change.cpp
  ../other.cpp
  ../knapsack.cpp
  ../max_sub_array_sum.cpp
  ../min_edit_distance.cpp
  ../max_coins.cpp
  ../longest_common_subsquence.cpp
  ../regex.cpp
  ../kmp_match.cpp
  ../interval_schedule.cpp
  ../house_robber.cpp
  ../longest_increasing_subsquence.cpp
  ../super_egg_drop.cpp
  ../game.cpp
)

target_link_libraries(dynamic_program_test
  ${GTEST_BOTH_LIBRARIES}
  pthread
)

add_test(dynamic_program_test
  ${CMAKE_CURRENT_BINARY_DIR}/dynamic_program_test
)
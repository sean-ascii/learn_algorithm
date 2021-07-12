#include <gtest/gtest.h>
#include "stl/my_shared_ptr.h"

TEST(STL_TEST, shared_ptr_test) {
  using namespace sakabatou_algorithm::stl;
  MySharedPtr<int> ptr(new int(1));
}
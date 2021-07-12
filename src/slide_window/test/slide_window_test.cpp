#include <gtest/gtest.h>

#include "slide_window/min_substring.h"
#include "slide_window/check_inclusion.h"
#include "slide_window/longest_unrepeated_substring.h"

TEST(SlideWindowTest, min_substring_test) {
  using namespace sakabatou_algorithm::slide_window;
  std::string s = "ADOBECODEBANC", t = "ABC";
  ASSERT_EQ("BANC", min_substring(s, t));
}

TEST(SlideWindowTest, check_inclusion_test) {
  using namespace sakabatou_algorithm::slide_window;
  ASSERT_TRUE(check_inclusion("eidbaooo", "ab"));
  ASSERT_FALSE(check_inclusion("eidboaoo", "ab"));
}

TEST(SlideWindowTest, check_all_inclusion_test) {
  using namespace sakabatou_algorithm::slide_window;
  std::vector<int> result{0, 6};
  ASSERT_EQ(result, check_all_inclusion("cbaebabacd", "abc"));
}

TEST(SlideWindowTest, longest_unrepeated_substring_test) {
  using namespace sakabatou_algorithm::slide_window;
  ASSERT_EQ("abc", longest_unrepeated_substring("abcabcbb"));
  ASSERT_EQ("b", longest_unrepeated_substring("bbbbb"));
  ASSERT_EQ("wke", longest_unrepeated_substring("pwwkew"));
}
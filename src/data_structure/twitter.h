#pragma once

#include <list>

namespace sakabatou_algorithm {
namespace data_structure {

class Twitter {
 public:
  void postTweet(int user_id, int tweet_id);
  std::list<int> getNewsFeed(int user_id);
  void follow(int follower_id, int followee_id);
  void unfollow(int follower_id, int followee_id);

 private:
  

};

} // data_structure
} // sakabatou_algorithm

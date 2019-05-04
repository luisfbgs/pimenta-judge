#ifndef ATTEMPT_H
#define ATTEMPT_H

#include "json.hpp"

namespace Attempt {

void fix();

std::string create(JSON&& att, const std::vector<uint8_t>& src);

JSON get(int id, int user);
JSON page(
  int user,
  unsigned page = 0,
  unsigned page_size = 0,
  int contest = 0,
  bool scoreboard = false,
  bool profile = false
);
JSON getcases(int user, int id);
JSON get_user_contest(int user, int user_id, int contest_id);
} // namespace Attempt

#endif

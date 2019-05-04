#ifndef USER_H
#define USER_H

#include "json.hpp"

namespace User {

int login(const std::string& username, const std::string& password); // id
bool change_password(const int id, const std::string& oldpassword, const std::string& newpassword);
JSON get(int id);
std::string name(int id);
JSON profile(int id, int user, unsigned page = 0, unsigned page_size = 0);
JSON page(int user, unsigned page = 0, unsigned page_size = 0);
JSON get_turmas(int user);
JSON get_of_turma(int user, const std::string& turma);
JSON isadmin(int user);
} // namespace User

#endif

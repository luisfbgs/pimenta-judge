#include <set>

#include "user.hpp"

#include "cmap.hpp"
#include "helper.hpp"
#include "database.hpp"
#include "attempt.hpp"

using namespace std;

namespace User {

int login(const string& username, const string& password) {
  DB(users);
  JSON user = users.retrieve(map<string,JSON>{
    {"username", username},
    {"password", password}
  });
  if (user.size() == 0) return 0;
  return user(0,"id");
}

bool change_password(const int id, const std::string& oldpassword, const std::string& newpassword){
  DB(users);

  JSON user;
  users.retrieve(id, user);
  
  if(user["password"] != oldpassword) return false;

  user["password"] = newpassword;
  users.update(id, user);

  return true;
}


JSON get(int id) {
  DB(users);
  return users.retrieve(id);
}

JSON isadmin(int user){
    if(!user || get(user)["turma"] != "Z") return JSON(false);
    return JSON(true);
}

JSON get_turmas(int user){
    JSON ans(vector<JSON>{});

    if(!user) return ans;
    if(get(user)["turma"] != "Z") return ans;

    DB(users);

    JSON us = users.retrieve();

    set<string> turmas;
    JSON tmp;
    for(JSON u : us.arr()){
        string s = u["turma"];
        turmas.insert(s);
    }

    for(const string& t : turmas){
        tmp["name"] = t;
        ans.push_back(tmp);
    }
    return ans;
}

JSON get_of_turma(int user, const string& turma){
    JSON ans(vector<JSON>{});

    if(!user || get(user)["turma"] != "Z") return ans;

    DB(users);

    JSON us = users.retrieve();
    for(JSON u : us.arr()) if(turma == u["turma"]) {
        u.erase("password");
        u.erase("turma");
        u.erase("username");
        ans.push_back(u);
    }
    return ans;
}

string name(int id) {
  JSON tmp = get(id);
  if (!tmp) return "";
  return tmp["name"];
}

JSON profile(int id, int user, unsigned p, unsigned ps) {
  JSON tmp = get(id);
  if (!tmp) return tmp;
  cmap<int,string> ans0;
  JSON atts = Attempt::page(user,0,0,0,false,true);
  for (auto& att : atts.arr()) {
    if (
      int(att["user"]) == id &&
      att["status"].str() == "judged" &&
      verdict_toi(att["verdict"]) == AC
    ) ans0[att["problem"]["id"]] = att["problem"]["name"].str();
  }
  if (!ps) {
    p = 0;
    ps = ans0.size();
  }
  JSON ans(map<string,JSON>{{"name",tmp["name"]},{"solved",vector<JSON>{}}});
  if (ans0.size() <= p*ps) return ans;
  auto it = ans0.at(p*ps);
  for (int i = 0; i < ps && it != ans0.end(); i++, it++) {
    ans["solved"].push_back(map<string,JSON>{
      {"id"   , it->first},
      {"name" , it->second}
    });
  }
  return ans;
}

JSON page(int user, unsigned p, unsigned ps) {
  struct stats {
    set<int> solved, tried;
  };
  map<int,stats> info;
  JSON atts = Attempt::page(user,0,0,0,false,true);
  for (auto& att : atts.arr()) {
    auto& us = info[att["user"]];
    us.tried.insert(int(att["problem"]["id"]));
    if (att["status"].str() == "judged" && verdict_toi(att["verdict"]) == AC) {
      us.solved.insert(int(att["problem"]["id"]));
    }
  }
  DB(users);
  JSON tmp = users.retrieve(), ans(vector<JSON>{});
  if (!ps) {
    p = 0;
    ps = tmp.size();
  }
  for (int i = p*ps, j = 0; i < tmp.size() && j < ps; i++, j++) {
    auto& us = tmp[i];
    ans.push_back(map<string,JSON>{
      {"id"     , us["id"]},
      {"name"   , us["name"]},
      {"solved" , info[us["id"]].solved.size()},
      {"tried"  , info[us["id"]].tried.size()}
    });
  }
  return ans;
}

} // namespace User

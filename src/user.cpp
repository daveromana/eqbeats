#include <sstream>
#include "user.h"
#include "utils.h"

User::User(int nId){
    _id = 0;
    if(nId<=0) return;

    DB::Result r = DB::query("SELECT name FROM Users WHERE id=" + number(nId));
    if(!r.empty()){
        _id = nId;
        _name = r[0][0];
    }
} 

std::string User::url(int id){
    std::stringstream s;
    s << "/user/" << id;
    return s.str();
}

std::vector<User> User::listHelper(bool artists, unsigned int n, unsigned int begin){
    return resultToVector(DB::query(
        "SELECT id, name FROM users " +
        (std::string) (artists? "WHERE EXISTS ( SELECT 1 FROM tracks WHERE user_id = users.id AND visible = 't' ) " : "") +
        "ORDER BY lower(name) ASC LIMIT "+number(n)+" OFFSET "+number(begin)));
}

std::vector<User> User::resultToVector(const DB::Result &r){
    std::vector<User> users(r.size());
    for(unsigned i=0; i<r.size(); i++)
        users[i] = User(number(r[i][0]), r[i][1]);
    return users; 
}

std::vector<User> User::list(unsigned int n, unsigned int begin){
    return listHelper(false, n, begin);
}

std::vector<User> User::listArtists(unsigned int n, unsigned int begin){
    return listHelper(true, n, begin);
}

std::vector<User> User::search(const std::string &q){
    return resultToVector(DB::query(
        "SELECT id, name FROM users WHERE name ILIKE $1 ORDER BY registration DESC", "%"+q+"%"));
}
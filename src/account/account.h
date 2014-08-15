#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "user.h"

class Account: public User {

    public:

        Account(){}
        Account(User u){id = u.id, name = u.name;}
        Account(int nId);

        std::string email;
        std::string about;
        bool notify;
        std::string license;

        int num_favs;
        int num_followers;

        void fill(Dict*) const;

        static void deleteAccount(int id);

};

#endif // ACCOUNT_H

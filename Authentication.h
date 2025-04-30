#ifndef _AUTHENTICATION_H_
#define _AUTHENTICATION_H_
#include "User.h"
#include <vector>
#include <memory>
using std::vector, std::shared_ptr, std::make_shared;


class Authentication {
public:
    static bool registerUser(vector<shared_ptr<IUser>>&, const string&, const string&, const string&);
    static shared_ptr<IUser> loginUser(const vector<shared_ptr<IUser>>&, const string&, const string&);
};

#endif
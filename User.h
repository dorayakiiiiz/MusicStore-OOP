#ifndef _USER_H_
#define _USER_H_

#include "Order.h"
#include <string>
#include <vector>
#include <iostream>
using std::string, std::vector, std::cout;

class IUser {
private:
    string username;
    string password;
public:
    virtual ~IUser();
    IUser(const string&, const string&);
    virtual string getRole() const = 0;
    string getUsername() const;
    string getPassword() const;
    void displayInfo() const;
};

class Customer : public IUser {
public:
    Customer(const string&, const string&);
    Customer(const Customer&);
    string getRole() const override;
};


// class AdminPasskey {
// private:
//     inline static vector<string> passKeys = {"23120197", "23120209"};
// public:
//     static bool isValid(const string&);
//     static void addPasskey(const string&);
// };

class Admin : public IUser {
private:
    inline static vector<string> passKeys = {"23120197", "23120209"};
public:
    Admin(const string&, const string&);
    Admin(const Admin&);
    string getRole() const override;
    static bool isValidPasskey(const string&);
};

#endif
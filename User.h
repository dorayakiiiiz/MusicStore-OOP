#ifndef _USER_H_
#define _USER_H_

#include "Order.h"
#include <string>
#include <vector>
#include <iostream>
using std::string, std::vector, std::cout;


class Customer  {
private:
    string username;
    string password;
    vector<Order> purchaseHistory;
public:
    Customer(const string&, const string&);
public:

    string getUsername() const;
    string getPassword() const;
    string getRole() const;
    void addPurchase(const Order&);
    const vector<Order>& getPurchaseHistory() const;
};

// singleton pattern for Admin Passkey
class AdminPasskey {
private:
    inline static AdminPasskey* instance = nullptr;
    vector<string> passKeys;
    AdminPasskey();
public:
    static AdminPasskey* getInstance();
    bool isValid(const string&) const;
    void addPasskey(const string&);
};

class Admin {
private:
    AdminPasskey* adminPasskey;
public:
    Admin();
public:
    string getRole() const;
};

#endif
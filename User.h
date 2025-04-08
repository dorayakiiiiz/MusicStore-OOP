#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <vector>
using std::string, std::vector;


class Customer  {
private:
    string username;
    string password;
    vector<string> purchaseHistory;
public:
    Customer(const string&, const string&);
public:

    string getUsername() const;
    string getPassword() const;
    string getRole() const;
    void addPurchase(const string& item);
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
    void addPassket(const string&);
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
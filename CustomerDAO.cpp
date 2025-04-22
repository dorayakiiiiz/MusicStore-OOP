#include "CustomerDAO.h"
#include <fstream>
#include <sstream>
using std::ifstream, std::ofstream, std::stringstream, std::string, std::vector, std::cout, std::endl;

void CustomerDAO::loadCustomers(vector<shared_ptr<Customer>>& users) {
    ifstream file("customer_info.txt");
    if (!file.is_open()) {
        throw "Error opening customer_info.txt!";
        return;
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;

        getline(ss, username, ',');
        getline(ss, password, ',');

        users.push_back(make_shared<Customer>(username, password));

    }
    file.close();
}


void CustomerDAO::saveCustomers(const vector<shared_ptr<Customer>>& users) {
    ofstream file("customer_info.txt");
    if (!file.is_open()) {
        throw "Error opening customer_info.txt!";
        return;
    }

    file << "Username,Password\n";
    for (int i = 0; i < users.size(); ++i) {
        file << users[i]->getUsername() << "," << users[i]->getPassword() << "\n";
    }

    file.close();
}
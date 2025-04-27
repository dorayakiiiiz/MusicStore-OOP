#include "DiscountDAO.h"
#include <fstream>
#include <sstream>
#include <iostream>

using std::ifstream, std::ofstream, std::stringstream, std::string, std::vector, std::cout, std::endl;

void DiscountDAO::loadDiscount(vector<IDiscount*>& vouchers) {
    ifstream file("vouchers.txt");
    if (!file.is_open()) {
        return;
    }
    string line;
    while (getline(file, line)) {
        IDiscount* voucher = IDiscount::toDiscount(line);
        vouchers.push_back(voucher);
    }
    file.close();
}

void DiscountDAO::saveDiscount(const vector<IDiscount*>& vouchers) {
    ofstream file("vouchers.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Error opening vouchers.txt");
    }
    for (const auto& voucher : vouchers) {
        file << voucher->toString() << "\n";
    }
    file.close();
}
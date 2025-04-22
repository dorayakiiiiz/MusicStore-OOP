#include "VoucherDAO.h"
#include <fstream>
#include <sstream>
#include <iostream>
using std::ifstream, std::ofstream, std::stringstream, std::string, std::vector, std::cout, std::endl;

void VoucherDAO::loadVoucher(vector<string>& vouchers) {
    ifstream file("vouchers.txt");
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        vouchers.push_back(line);
    }
    file.close();
}

void VoucherDAO::saveVoucher(const vector<string>& vouchers) {
    ofstream file("vouchers.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Error opening vouchers.txt");
    }

    for (const auto& voucher : vouchers) {
        file << voucher << "\n";
    }
    file.close();
}
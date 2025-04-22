#ifndef _VOUCHER_DAO_H_
#define _VOUCHER_DAO_H_
#include <vector>
#include <string>
using std::vector, std::string;

class VoucherDAO {
public:
    static void loadVoucher(vector<string>&);
    static void saveVoucher(const vector<string>&);
};

#endif
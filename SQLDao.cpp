#include "SqlDao.h"

using std::make_shared, std::shared_ptr;

// return the sql music repository
shared_ptr<IRepository<Music>> SqlDao::music() {
    return make_shared<SqlMusicRepository>();
}

// return the sql user repository
shared_ptr<IRepository<shared_ptr<User>>> SqlDao::user() {
    return make_shared<SqlUserRepository>();
}

// return the sql order repository
shared_ptr<IRepository<Order>> SqlDao::order() {
    return make_shared<SqlOrderRepository>();
}

// return the sql discount repository
shared_ptr<IRepository<shared_ptr<Discount>>> SqlDao::discount() {
    return make_shared<SqlDiscountRepository>();
}

// return the sql sales record repository
shared_ptr<IRepository<SalesRecord>> SqlDao::salesRecord() {
    return make_shared<SqlSalesRecordRepository>();
}

#ifndef MOCK_SQL_DAO_H
#define MOCK_SQL_DAO_H

#include "../IDataProvider.h"
#include "../Music.h"
#include "../User.h"
#include "../Order.h"
#include "../Discount.h"
#include "../SalesRecord.h"
#include <memory>
#include <vector>
#include <algorithm>

// Mock implementation for IRepository<Music>
class MockMusicRepository : public IRepository<Music> {
private:
    std::vector<Music> items;

public:
    std::vector<Music> getAll() override { 
        return items; 
    }
    
    Music getById(int id) override {
        if (id > 0 && id <= items.size()) {
            return items[id - 1];
        }
        return Music();
    }
    
    bool add(const Music& item) override {
        // Check for duplicates
        for (const auto& existing : items) {
            if (existing == item) {
                return false;
            }
        }
        items.push_back(item);
        return true;
    }
    
    bool updateById(int id, const Music& item) override {
        if (id > 0 && id <= items.size()) {
            items[id - 1] = item;
            return true;
        }
        return false;
    }
    
    bool deleteById(int id) override {
        if (id > 0 && id <= items.size()) {
            items.erase(items.begin() + (id - 1));
            return true;
        }
        return false;
    }
    
    // Helper for tests
    void setItems(const std::vector<Music>& newItems) {
        items = newItems;
    }
};

// Mock implementation for IRepository<shared_ptr<User>>
class MockUserRepository : public IRepository<std::shared_ptr<User>> {
private:
    std::vector<std::shared_ptr<User>> users;

public:
    std::vector<std::shared_ptr<User>> getAll() override {
        return users;
    }
    
    std::shared_ptr<User> getById(int id) override {
        if (id > 0 && id <= users.size()) {
            return users[id - 1];
        }
        return nullptr;
    }
    
    bool add(const std::shared_ptr<User>& user) override {
        // Check for duplicate usernames
        for (const auto& existing : users) {
            if (existing->getUsername() == user->getUsername()) {
                return false;
            }
        }
        users.push_back(user);
        return true;
    }
    
    bool updateById(int id, const std::shared_ptr<User>& user) override {
        if (id > 0 && id <= users.size()) {
            users[id - 1] = user;
            return true;
        }
        return false;
    }
    
    bool deleteById(int id) override {
        if (id > 0 && id <= users.size()) {
            users.erase(users.begin() + (id - 1));
            return true;
        }
        return false;
    }
    
    // Helper for tests
    void setUsers(const std::vector<std::shared_ptr<User>>& newUsers) {
        users = newUsers;
    }
};

// Mock implementation for IRepository<Order>
class MockOrderRepository : public IRepository<Order> {
private:
    std::vector<Order> orders;

public:
    std::vector<Order> getAll() override {
        return orders;
    }
    
    Order getById(int id) override {
        if (id > 0 && id <= orders.size()) {
            return orders[id - 1];
        }
        // Return default order
        return Order("", {}, 0.0f);
    }
    
    bool add(const Order& order) override {
        orders.push_back(order);
        return true;
    }
    
    bool updateById(int id, const Order& order) override {
        if (id > 0 && id <= orders.size()) {
            orders[id - 1] = order;
            return true;
        }
        return false;
    }
    
    bool deleteById(int id) override {
        if (id > 0 && id <= orders.size()) {
            orders.erase(orders.begin() + (id - 1));
            return true;
        }
        return false;
    }
    
    // Helper for tests
    void setOrders(const std::vector<Order>& newOrders) {
        orders = newOrders;
    }
};

// Mock implementation for IRepository<shared_ptr<Discount>>
class MockDiscountRepository : public IRepository<std::shared_ptr<Discount>> {
private:
    std::vector<std::shared_ptr<Discount>> discounts;

public:
    std::vector<std::shared_ptr<Discount>> getAll() override {
        return discounts;
    }
    
    std::shared_ptr<Discount> getById(int id) override {
        if (id > 0 && id <= discounts.size()) {
            return discounts[id - 1];
        }
        return nullptr;
    }
    
    bool add(const std::shared_ptr<Discount>& discount) override {
        // Check for duplicate codes
        for (const auto& existing : discounts) {
            if (existing->getCode() == discount->getCode()) {
                return false;
            }
        }
        discounts.push_back(discount);
        return true;
    }
    
    bool updateById(int id, const std::shared_ptr<Discount>& discount) override {
        if (id > 0 && id <= discounts.size()) {
            discounts[id - 1] = discount;
            return true;
        }
        return false;
    }
    
    bool deleteById(int id) override {
        if (id > 0 && id <= discounts.size()) {
            discounts.erase(discounts.begin() + (id - 1));
            return true;
        }
        return false;
    }
    
    // Helper for tests
    void setDiscounts(const std::vector<std::shared_ptr<Discount>>& newDiscounts) {
        discounts = newDiscounts;
    }
};

// Mock implementation for IRepository<SalesRecord>
class MockSalesRecordRepository : public IRepository<SalesRecord> {
private:
    std::vector<SalesRecord> records;

public:
    std::vector<SalesRecord> getAll() override {
        return records;
    }
    
    SalesRecord getById(int id) override {
        if (id > 0 && id <= records.size()) {
            return records[id - 1];
        }
        return SalesRecord();
    }
    
    bool add(const SalesRecord& record) override {
    // Kiểm tra nếu record đã tồn tại (dựa trên name và artist)
    for (auto& existingRecord : records) {
        if (existingRecord.getName() == record.getName() && 
            existingRecord.getArtist() == record.getArtist()) {
            // Nếu đã có, cập nhật thông tin thay vì thêm mới
            // Code thật sẽ làm việc này trong SQLSalesRecordRepository
            return true;
        }
    }
    
    // Nếu không tìm thấy, thêm mới
    records.push_back(record);
    return true;
}
    
    bool updateById(int id, const SalesRecord& record) override {
        if (id > 0 && id <= records.size()) {
            records[id - 1] = record;
            return true;
        }
        return false;
    }
    
    bool deleteById(int id) override {
        if (id > 0 && id <= records.size()) {
            records.erase(records.begin() + (id - 1));
            return true;
        }
        return false;
    }
    
    // Helper for tests
    void setRecords(const std::vector<SalesRecord>& newRecords) {
        records = newRecords;
    }
};

// Mock SqlDao implementation
class MockDao : public IDataProvider {
private:
    std::shared_ptr<MockMusicRepository> musicRepo;
    std::shared_ptr<MockUserRepository> userRepo;
    std::shared_ptr<MockOrderRepository> orderRepo;
    std::shared_ptr<MockDiscountRepository> discountRepo;
    std::shared_ptr<MockSalesRecordRepository> salesRecordRepo;

public:
    MockDao() {
        musicRepo = std::make_shared<MockMusicRepository>();
        userRepo = std::make_shared<MockUserRepository>();
        orderRepo = std::make_shared<MockOrderRepository>();
        discountRepo = std::make_shared<MockDiscountRepository>();
        salesRecordRepo = std::make_shared<MockSalesRecordRepository>();
    }

    std::shared_ptr<IRepository<Music>> music() override {
        return musicRepo;
    }
    
    std::shared_ptr<IRepository<std::shared_ptr<User>>> user() override {
        return userRepo;
    }
    
    std::shared_ptr<IRepository<Order>> order() override {
        return orderRepo;
    }
    
    std::shared_ptr<IRepository<std::shared_ptr<Discount>>> discount() override {
        return discountRepo;
    }
    
    std::shared_ptr<IRepository<SalesRecord>> salesRecord() override {
        return salesRecordRepo;
    }
    
    // Helpers for testing
    void setMusicItems(const std::vector<Music>& items) {
        std::static_pointer_cast<MockMusicRepository>(musicRepo)->setItems(items);
    }
    
    void setUsers(const std::vector<std::shared_ptr<User>>& users) {
        std::static_pointer_cast<MockUserRepository>(userRepo)->setUsers(users);
    }
    
    void setOrders(const std::vector<Order>& orders) {
        std::static_pointer_cast<MockOrderRepository>(orderRepo)->setOrders(orders);
    }
    
    void setDiscounts(const std::vector<std::shared_ptr<Discount>>& discounts) {
        std::static_pointer_cast<MockDiscountRepository>(discountRepo)->setDiscounts(discounts);
    }
    
    void setSalesRecords(const std::vector<SalesRecord>& records) {
        std::static_pointer_cast<MockSalesRecordRepository>(salesRecordRepo)->setRecords(records);
    }
};

#endif
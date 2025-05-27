#ifndef MOCK_SQL_DAO_H
#define MOCK_SQL_DAO_H

#include "../source/database/IDataProvider.h"
#include "../source/models/Music.h"
#include "../source/models/User.h"
#include "../source/models/Order.h"
#include "../source/models/Discount.h"
#include "../source/models/SalesRecord.h"
#include <memory>
#include <vector>

// Mock repository implementation for Music
class MockMusicRepository : public IRepository<Music> {
private:
    std::vector<Music> items;
public:
    std::vector<Music> getAll() override { return items; }
    
    Music getById(int id) override { 
        if (id > 0 && id <= items.size()) {
            return items[id-1];
        }
        return Music(); 
    }
    
    bool add(const Music& entity) override { 
        for (const auto& item : items) {
            if (item == entity) return false; // Check for duplicates
        }
        items.push_back(entity); 
        return true;
    }
    
    bool updateById(int id, const Music& entity) override {
        if (id > 0 && id <= items.size()) {
            items[id-1] = entity;
            return true;
        }
        return false;
    }
    
    bool deleteById(int id) override {
        if (id > 0 && id <= items.size()) {
            items.erase(items.begin() + (id-1));
            return true;
        }
        return false;
    }
    
    void setItems(const std::vector<Music>& newItems) {
        items = newItems;
    }
};

// Mock repository implementation for User
class MockUserRepository : public IRepository<std::shared_ptr<User>> {
private:
    std::vector<std::shared_ptr<User>> users;
public:
    std::vector<std::shared_ptr<User>> getAll() override { return users; }
    
    std::shared_ptr<User> getById(int id) override { 
        if (id > 0 && id <= users.size()) {
            return users[id-1];
        }
        return nullptr; 
    }
    
    bool add(const std::shared_ptr<User>& entity) override { 
        for (const auto& user : users) {
            if (user->getUsername() == entity->getUsername()) return false;
        }
        users.push_back(entity); 
        return true;
    }
    
    bool updateById(int id, const std::shared_ptr<User>& entity) override {
        if (id > 0 && id <= users.size()) {
            users[id-1] = entity;
            return true;
        }
        return false;
    }
    
    bool deleteById(int id) override {
        if (id > 0 && id <= users.size()) {
            users.erase(users.begin() + (id-1));
            return true;
        }
        return false;
    }
    
    void setUsers(const std::vector<std::shared_ptr<User>>& newUsers) {
        users = newUsers;
    }
};

// Mock repository implementation for Order
class MockOrderRepository : public IRepository<Order> {
private:
    std::vector<Order> orders;
public:
    std::vector<Order> getAll() override { return orders; }
    
    Order getById(int id) override { 
        if (id > 0 && id <= orders.size()) {
            return orders[id-1];
        }
        return Order(); 
    }
    
    bool add(const Order& entity) override { 
        orders.push_back(entity); 
        return true;
    }
    
    bool updateById(int id, const Order& entity) override {
        if (id > 0 && id <= orders.size()) {
            orders[id-1] = entity;
            return true;
        }
        return false;
    }
    
    bool deleteById(int id) override {
        if (id > 0 && id <= orders.size()) {
            orders.erase(orders.begin() + (id-1));
            return true;
        }
        return false;
    }
    
    void setOrders(const std::vector<Order>& newOrders) {
        orders = newOrders;
    }
};

// Mock repository implementation for Discount
class MockDiscountRepository : public IRepository<std::shared_ptr<Discount>> {
private:
    std::vector<std::shared_ptr<Discount>> discounts;
public:
    std::vector<std::shared_ptr<Discount>> getAll() override { return discounts; }
    
    std::shared_ptr<Discount> getById(int id) override { 
        if (id > 0 && id <= discounts.size()) {
            return discounts[id-1];
        }
        return nullptr; 
    }
    
    bool add(const std::shared_ptr<Discount>& entity) override { 
        for (const auto& discount : discounts) {
            if (discount->getCode() == entity->getCode()) return false;
        }
        discounts.push_back(entity); 
        return true;
    }
    
    bool updateById(int id, const std::shared_ptr<Discount>& entity) override {
        if (id > 0 && id <= discounts.size()) {
            discounts[id-1] = entity;
            return true;
        }
        return false;
    }
    
    bool deleteById(int id) override {
        if (id > 0 && id <= discounts.size()) {
            discounts.erase(discounts.begin() + (id-1));
            return true;
        }
        return false;
    }
    
    void setDiscounts(const std::vector<std::shared_ptr<Discount>>& newDiscounts) {
        discounts = newDiscounts;
    }
};

// Mock repository implementation for SalesRecord
class MockSalesRecordRepository : public IRepository<SalesRecord> {
private:
    std::vector<SalesRecord> records;
public:
    std::vector<SalesRecord> getAll() override { return records; }
    
    SalesRecord getById(int id) override { 
        if (id > 0 && id <= records.size()) {
            return records[id-1];
        }
        return SalesRecord(); 
    }
    
    // Implementation for add() in MockSalesRecordRepository:
    bool add(const SalesRecord& entity) override {
        // Check if record with same name and artist already exists
        for (auto& record : records) {
            if (record.getName() == entity.getName() && record.getArtist() == entity.getArtist()) {
                // Update existing record by adding sold quantities and revenue
                int newSold = record.getSold() + entity.getSold();
                float newRevenue = record.getRevenue() + entity.getRevenue();
                
                // We can't directly modify the record, so we need to replace it
                // (In a real implementation, this would be an SQL UPDATE)
                record = SalesRecord(
                    record.getName(),
                    record.getArtist(),
                    record.getGenre(),
                    newSold,
                    newRevenue
                );
                return true;
            }
        }
        
        // If no matching record found, add as new
        records.push_back(entity);
        return true;
    }
        
    bool updateById(int id, const SalesRecord& entity) override {
        if (id > 0 && id <= records.size()) {
            records[id-1] = entity;
            return true;
        }
        return false;
    }
    
    bool deleteById(int id) override {
        if (id > 0 && id <= records.size()) {
            records.erase(records.begin() + (id-1));
            return true;
        }
        return false;
    }
    
    void setRecords(const std::vector<SalesRecord>& newRecords) {
        records = newRecords;
    }
};

// Main mock data provider that implements IDataProvider
class MockSqlDao : public IDataProvider {
private:
    std::shared_ptr<MockMusicRepository> musicRepo;
    std::shared_ptr<MockUserRepository> userRepo;
    std::shared_ptr<MockOrderRepository> orderRepo;
    std::shared_ptr<MockDiscountRepository> discountRepo;
    std::shared_ptr<MockSalesRecordRepository> salesRecordRepo;

public:
    MockSqlDao() {
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

    // Helper methods for setting test data
    void setMusicItems(const std::vector<Music>& items) {
        musicRepo->setItems(items);
    }

    void setUsers(const std::vector<std::shared_ptr<User>>& users) {
        userRepo->setUsers(users);
    }

    void setOrders(const std::vector<Order>& orders) {
        orderRepo->setOrders(orders);
    }

    void setDiscounts(const std::vector<std::shared_ptr<Discount>>& discounts) {
        discountRepo->setDiscounts(discounts);
    }

    void setSalesRecords(const std::vector<SalesRecord>& records) {
        salesRecordRepo->setRecords(records);
    }
};

#endif // MOCK_SQL_DAO_H
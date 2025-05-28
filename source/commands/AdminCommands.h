#ifndef _ADMIN_COMMANDS_H_
#define _ADMIN_COMMANDS_H_

#include "Command.h"
#include "../models/User.h"
#include <memory>
#include <string>

using std::shared_ptr;

// Forward declarations
class Music;

/**
 * @brief Command to view music list
 */
class ViewMusicListCommand : public Command {
public:
    string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to add new music items
 */
class AddNewItemsCommand : public Command {
public:
    string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to remove music items
 */
class RemoveItemsCommand : public Command {
public:
    string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to update item prices
 */
class UpdatePriceCommand : public Command {
public:
    string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to view user list
 */
class ViewUsersCommand : public Command {
public:
    string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to view purchase history for all customers
 */
class ViewAllPurchaseHistoriesCommand : public Command {
public:
    string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to delete users
 */
class DeleteUserCommand : public Command {
private:
    shared_ptr<User>& _currentUser;

public:
    DeleteUserCommand(shared_ptr<User>& user);
    string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to view sales statistics
 */
class ViewSalesStatisticsCommand : public Command {
public:
    string getName() const override;
    bool execute() override;
};

/**
 * @brief Command for admin logout
 */
class AdminLogoutCommand : public Command {
private:
    shared_ptr<User>& _currentUser;
    
public:
    AdminLogoutCommand(shared_ptr<User>& user);
    string getName() const override;
    bool execute() override;
};

#endif

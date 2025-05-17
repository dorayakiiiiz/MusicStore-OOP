#ifndef _ADMIN_COMMANDS_H_
#define _ADMIN_COMMANDS_H_

#include "Command.h"
#include "User.h"
#include <memory>
#include <string>

// Forward declarations
class Music;

/**
 * @brief Command to view music list
 */
class ViewMusicListCommand : public Command {
public:
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to add new music items
 */
class AddNewItemsCommand : public Command {
public:
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to remove music items
 */
class RemoveItemsCommand : public Command {
public:
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to update item prices
 */
class UpdatePriceCommand : public Command {
public:
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to view user list
 */
class ViewUsersCommand : public Command {
public:
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to view purchase history for all customers
 */
class ViewAllPurchaseHistoriesCommand : public Command {
public:
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to delete users
 */
class DeleteUserCommand : public Command {
private:
    std::shared_ptr<User>& currentUser;

public:
    DeleteUserCommand(std::shared_ptr<User>& user);
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to view sales statistics
 */
class ViewSalesStatisticsCommand : public Command {
public:
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command for admin logout
 */
class AdminLogoutCommand : public Command {
private:
    std::shared_ptr<User>& currentUser;
    
public:
    AdminLogoutCommand(std::shared_ptr<User>& user);
    std::string getName() const override;
    bool execute() override;
};

#endif

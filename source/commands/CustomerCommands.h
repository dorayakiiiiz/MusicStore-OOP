#ifndef _CUSTOMER_COMMANDS_H_
#define _CUSTOMER_COMMANDS_H_

#include "Command.h"
#include "../models/User.h"
#include "../models/Cart.h"
#include <memory>
#include <string>

/**
 * @brief Command to view purchase history
 */
class ViewPurchaseHistoryCommand : public Command {
private:
    std::shared_ptr<User>& _currentUser;
    
public:
    ViewPurchaseHistoryCommand(std::shared_ptr<User>& user);
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to view music list
 */
class ViewMusicCommand : public Command {
public:
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to search for music
 */
class SearchMusicCommand : public Command {
public:
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to add items to cart
 */
class AddToCartCommand : public Command {
private:
    Cart& _cart;
    
public:
    AddToCartCommand(Cart& c);
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to view current cart
 */
class ViewCurrentCartCommand : public Command {
private:
    Cart& _cart;
    
public:
    ViewCurrentCartCommand(Cart& c);
    std::string getName() const override;
    bool execute() override;
};


/**
 * @brief Command to remove items from cart
 */
class RemoveFromCartCommand : public Command {
private:
    Cart& _cart;
    
public:
    RemoveFromCartCommand(Cart& c);
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command to checkout
 */
class CheckoutCommand : public Command {
private:
    Cart& _cart;
    std::shared_ptr<User>& _currentUser;
    
public:
    CheckoutCommand(Cart& c, std::shared_ptr<User>& user);
    std::string getName() const override;
    bool execute() override;
};

/**
 * @brief Command for customer logout
 */
class CustomerLogoutCommand : public Command {
private:
    Cart& _cart;
    std::shared_ptr<User>& _currentUser;
    
public:
    CustomerLogoutCommand(Cart& c, std::shared_ptr<User>& user);
    std::string getName() const override;
    bool execute() override;
};

#endif

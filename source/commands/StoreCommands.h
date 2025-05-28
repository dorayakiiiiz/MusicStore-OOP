#ifndef _STORE_COMMANDS_H_
#define _STORE_COMMANDS_H_

#include "Command.h"
#include <string>
#include <memory>
#include "../models/User.h"

using std::string, std::shared_ptr, std::make_shared;;

/**
 * @brief Command for user signup
 */
class SignUpCommand : public Command {
private:
    shared_ptr<User>& _currentUser;
    
public:
    SignUpCommand(shared_ptr<User>& user);
    string getName() const override;
    bool execute() override;
};

/**
 * @brief Command for user login
 */
class LoginCommand : public Command {
private:
    shared_ptr<User>& _currentUser;

public:
    LoginCommand(shared_ptr<User>& user);
    string getName() const override;
    bool execute() override;
};

/**
 * @brief Command for exiting the application
 */
class ExitCommand : public Command {
public:
    string getName() const override;
    bool execute() override;
};

#endif

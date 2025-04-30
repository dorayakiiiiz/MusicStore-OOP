#ifndef _ADMIN_CONTROLLER_H_
#define _ADMIN_CONTROLLER_H_

#include "IController.h"
#include "AdminUI.h"

class AdminController : public IController {
public:
    void menu(vector<Music>& items, vector<shared_ptr<IUser>>& users, vector<Order>& orders, vector<shared_ptr<IDiscount>>&, shared_ptr<IUser>& currentUser) override;
};


#endif
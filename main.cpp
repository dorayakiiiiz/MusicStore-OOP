#include "DatabaseManager.h"
#include "SystemManager.h"
#include "MusicItem.h"
#include "User.h"
#include "Discount.h"

#include <iostream>

using std::cin, std::cout;

int main() {
    
    SystemManager* systemManager = SystemManager::getInstance();
    systemManager->run();
    
    return 0;
}
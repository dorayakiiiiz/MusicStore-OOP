#include "CartService.h"
#include "IDataProvider.h"
#include "SQLDao.h"

// Constructor
CartService::CartService() {
    dataProvider = make_shared<SqlDao>();
}

// Get the singleton instance of CartService
shared_ptr<CartService> CartService::getInstance() {
    if (instance == nullptr) {
        instance = shared_ptr<CartService>(new CartService());
    }
    return instance;
}

// Add a music item to the shopping cart
bool CartService::addItemToCart(Cart& cart, int itemID, int quantity) {

    Music item = dataProvider->music()->getById(itemID);

    if (item.getQuantity() < quantity) {
        return false; // Not enough stock
    }

    // Add to cart and reduce inventory
    cart.addItems(item, quantity);
    

    item.updateQuantity(item.getQuantity() - quantity);
    dataProvider->music()->updateById(itemID, item);

    return true;
}

// Remove an item from the shopping cart
bool CartService::removeItemFromCart(Cart& cart, int itemID) {

    // Check if itemID is valid
    if (itemID < 0 || itemID >= cart.getItems().size()) {
        return false; // Invalid item ID
    }

    // get all items from the repository
    vector<Music> inventory = dataProvider->music()->getAll();
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i] == cart.getItems()[itemID]) {
            // add the item back to inventory
            inventory[i].updateQuantity(inventory[i].getQuantity() + cart.getItems()[itemID].getQuantity());
            dataProvider->music()->updateById(i + 1, inventory[i]);
            break;
        }
    }
    
    // Remove the item from cart
    cart.removeItem(itemID);
    return true;
}

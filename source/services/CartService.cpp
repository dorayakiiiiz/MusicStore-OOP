#include "CartService.h"
#include "../database/IDataProvider.h"
#include "../database/SQLDao.h"

// Constructor
CartService::CartService(shared_ptr<IDataProvider> provider) {
    this->_dataProvider = provider;
}

// Get the singleton instance of CartService
shared_ptr<CartService> CartService::getInstance(shared_ptr<IDataProvider> provider) {
    if (_instance == nullptr) {
        // If no provider is passed, use the default SqlDao
        if (!provider) {
            provider = make_shared<SqlDao>();
        }
        _instance = shared_ptr<CartService>(new CartService(provider));
    }
    return _instance;
}

// Add a music item to the shopping cart
bool CartService::addItemToCart(Cart& cart, int itemID, int quantity) {

    Music item = _dataProvider->music()->getById(itemID);

    if (item.getQuantity() < quantity) {
        return false; // Not enough stock
    }

    // Add to cart and reduce inventory
    cart.addItems(item, quantity);
    

    item.updateQuantity(item.getQuantity() - quantity);
    _dataProvider->music()->updateById(itemID, item);

    return true;
}

// Remove an item from the shopping cart
bool CartService::removeItemFromCart(Cart& cart, int itemID) {

    // Check if itemID is valid
    if (itemID < 0 || itemID >= cart.getItems().size()) {
        return false; // Invalid item ID
    }

    // get all items from the repository
    vector<Music> inventory = _dataProvider->music()->getAll();
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i] == cart.getItems()[itemID]) {
            // add the item back to inventory
            inventory[i].updateQuantity(inventory[i].getQuantity() + cart.getItems()[itemID].getQuantity());
            _dataProvider->music()->updateById(i + 1, inventory[i]);
            break;
        }
    }
    
    // Remove the item from cart
    cart.removeItem(itemID);
    return true;
}

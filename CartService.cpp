#include "CartService.h"
#include "Registry.h"
#include "IMusicRepository.h"

// Add a music item to the shopping cart
bool CartService::addItemToCart(Cart& cart, int itemID, int quantity) {

    Music item = Registry::getSingleton<IMusicRepository>()->getById(itemID);

    if (item.getQuantity() < quantity) {
        return false; // Not enough stock
    }

    // Add to cart and reduce inventory
    cart.addItems(item, quantity);

    item.updateQuantity(item.getQuantity() - quantity);
    Registry::getSingleton<IMusicRepository>()->updateById(itemID, item);

    return true;
}

// Remove an item from the shopping cart
bool CartService::removeItemFromCart(Cart& cart, int itemID) {

    // Check if itemID is valid
    if (itemID < 0 || itemID >= cart.getItems().size()) {
        return false; // Invalid item ID
    }

    // get all items from the repository
    vector<Music> inventory = Registry::getSingleton<IMusicRepository>()->getAll();
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i] == cart.getItems()[itemID]) {
            // add the item back to inventory
            inventory[i].updateQuantity(inventory[i].getQuantity() + cart.getItems()[itemID].getQuantity());
            Registry::getSingleton<IMusicRepository>()->updateById(i + 1, inventory[i]);
            break;
        }
    }
    
    // Remove the item from cart
    cart.removeItem(itemID);
    return true;
}

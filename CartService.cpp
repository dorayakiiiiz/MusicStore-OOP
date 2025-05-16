#include "CartService.h"
#include "Registry.h"
#include "IMusicRepository.h"

// Add a music item to the shopping cart
bool CartService::addItemToCart(Cart& cart, int itemID, int quantity) {
    // Get the music inventory from the repository
    vector<Music> inventory = Registry::getSingleton<IMusicRepository>()->getAll();
    // Validate quantity
    if (inventory[itemID].getQuantity() < quantity) {
        return false;
    }

    // Create a copy of the item with the requested quantity
    Music item = inventory[itemID];
    item.updateQuantity(quantity);
    
    // Add to cart and reduce inventory
    cart.addItems(item, quantity);
    inventory[itemID].updateQuantity(inventory[itemID].getQuantity() - quantity);
    // Update the inventory in the repository
    Registry::getSingleton<IMusicRepository>()->updateById(itemID + 1, inventory[itemID]);
    
    return true;
}

// Remove an item from the shopping cart
bool CartService::removeItemFromCart(Cart& cart, vector<Music>& inventory, int itemID) {

    // Add item quantity back to inventory
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i] == cart.getItems()[itemID]) {
            inventory[i].updateQuantity(inventory[i].getQuantity() + cart.getItems()[itemID].getQuantity());
            Registry::getSingleton<IMusicRepository>()->updateById(i + 1, inventory[i]);
            break;
        }
    }
    
    // Remove the item from cart
    cart.removeItem(itemID);
    return true;
}

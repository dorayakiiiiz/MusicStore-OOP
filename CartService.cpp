#include "CartService.h"

// Add a music item to the shopping cart
bool CartService::addItemToCart(Cart& cart, vector<Music>& inventory, int itemID, int quantity) {
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
    
    return true;
}

// Remove an item from the shopping cart
bool CartService::removeItemFromCart(Cart& cart, vector<Music>& inventory, int itemID) {

    // Add item quantity back to inventory
    for (auto& item : inventory) {
        if (item == cart.getItems()[itemID]) {
            item.updateQuantity(item.getQuantity() + cart.getItems()[itemID].getQuantity());
            break;
        }
    }
    
    // Remove the item from cart
    cart.removeItem(itemID);
    return true;
}

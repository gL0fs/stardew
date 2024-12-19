#ifndef __BACKPACK_H__
#define __BACKPACK_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>
#include <string>

class Item {
public:
    Item(const std::string& itemName, int itemQuantity);
    std::string name;    // Item name
    int quantity;        // Item quantity
    // Function to display item information
    void display(float x, float y, bool display) const;
    
};

class Inventory : public cocos2d::Layer {
private:
    std::vector<Item> items;
    size_t capacity;
    bool initial;
    cocos2d::ui::ImageView* bagImage;
public:
    Inventory(size_t c); // 私有构造函数
    virtual ~Inventory(); // 私有析构函数
    
    bool addItemToInventory(const std::string& name, int quantity);
    // Add an item to the inventory
    bool removeItem(const std::string& name, int quantity);

    // Remove an item from the inventory
    std::vector<Item> getItems();

    // Display the inventory contents (show all items)
    void displayInventory() ;
   

    // Get the maximum capacity of the inventory
    size_t getCapacity() const;

    // Get the number of items in the inventory
    size_t getItemCount() const;
};

#endif // __BACKPACK_H__

//Inventory playerInventory(10);
//playerInventory.addItem("Apple", 5);
//playerInventory.displayInventory();
//playerInventory.removeItem("Wood", 5);
  
    
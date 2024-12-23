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
    cocos2d::ui::Text* text;
    cocos2d::ui::ImageView* itemImage;
    void display(float x, float y, int size = 2) const;
    
};

class Inventory : public cocos2d::Layer {
private:
    std::vector<Item> items;
    size_t capacity;
    cocos2d::ui::ImageView* bagImage;
    size_t currentIndex;
public:
    Inventory(size_t c); // ˽�й��캯��
    virtual ~Inventory(); // ˽����������
    
    bool addItemToInventory(const std::string& name, int quantity);
    // Add an item to the inventory
    bool removeItem(const std::string& name, int quantity);
    bool isOpen();
    // Remove an item from the inventory
    std::vector<Item> getItems();

    void items_display(size_t currentIndex = -1) const;

    // Display the inventory contents (show all items)
    void displayInventory() const;
    void Inventory::eat();
    
    void updateSelectedItem(cocos2d::EventMouse* e);
    Item getSelectedItem() const;
    // Get the maximum capacity of the inventory
    size_t getCapacity() const;

    // Get the number of items in the inventory
    size_t getItemCount() const;
    void Inventory::cook();//���
};

#endif // __BACKPACK_H__

//Inventory playerInventory(10);
//playerInventory.addItem("Apple", 5);
//playerInventory.displayInventory();
//playerInventory.removeItem("Wood", 5);
  
    
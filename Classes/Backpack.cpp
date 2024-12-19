#include "Backpack.h"

USING_NS_CC;

// Constructor to initialize Item with name and quantity

Item::Item(const std::string& itemName, int itemQuantity) 
    : name(itemName), quantity(itemQuantity) {}

// Function to display item information
void Item::display(float x, float y, bool display) const {
    
    Vec2 position(x, y);
    auto text = ui::Text::create(std::to_string(quantity), "fonts/Marker Felt.ttf", 8);
    std::string png_name = name + ".png";
    auto itemImage = ui::ImageView::create(png_name);
    if (!display) {
        if (quantity != 1) {
            if (text) {
                text->setAnchorPoint(Vec2(-0.5, 1.3));
                text->setPosition(position);
                Director::getInstance()->getRunningScene()->addChild(text);
            }
            else {
                CCLOG("Failed to create label for item: %s", name.c_str());
            }
        }
        // 创建一个 Label 显示物品名称和数量
        
        // 检查 Label 是否成功创建
        if (itemImage) {
            // 设置标签的显示位置        
            itemImage->setScale(2);
            // 设置标签的显示位置
            itemImage->setPosition(position); // 使用传入的 x, y 作为位置
            // 将标签添加到父节点（ui 层）
            Director::getInstance()->getRunningScene()->addChild(itemImage);

        }
        else {
            CCLOG("Failed to create label for item: %s", name.c_str());
        }
    }
    else {
        if (text && quantity != 1) {
            itemImage->removeFromParentAndCleanup(true);
        }
        if (itemImage) {
            itemImage->removeFromParentAndCleanup(true);
        }
    }
}


Inventory::Inventory(size_t c) : capacity(c), items(), initial(false) {
    items.reserve(c);
    
    bagImage = ui::ImageView::create("bag.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 计算屏幕中央的坐标
    Vec2 centerPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30);  // 根据需要调整Y偏移
    // 设置 bagImage 的位置为视图中央
    bagImage->setPosition(centerPosition);
    bagImage->setScale(0.8);
    bagImage->setVisible(false);
    Director::getInstance()->getRunningScene()->addChild(bagImage);
    bagImage->retain();
}

Inventory::~Inventory()
{
    
}

bool Inventory::removeItem(const std::string& name, int quantity) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->name == name) {
            if (it->quantity >= quantity) {
                it->quantity -= quantity;
                if (it->quantity == 0) {
                    items.erase(it);
                }
                return true;
            }
            else {
                CCLOG("Not enough %s to remove.", name.c_str());
                return false;
            }
        }
    }
    //std::cout << name << " not found in inventory." << std::endl;
    return false;
}

bool Inventory::addItemToInventory(const std::string& name, int quantity) {
    if (items.empty()) {
        for (auto& item : items) {
            if (item.name == name) {
                item.quantity += quantity;
                return true;
            }
        }
        if (items.size() >= capacity) {
            CCLOG("Inventory is full! Cannot add %s.", name.c_str());
            return false;
        }
    }
    items.emplace_back(name, quantity);
    return true;
}

std::vector<Item> Inventory::getItems() {
    return items;
}

void Inventory::displayInventory(){
    bool isVisible = bagImage->isVisible();
    if (!isVisible) {
        Director::getInstance()->getRunningScene()->addChild(bagImage);   
    }
    else {
        Director::getInstance()->getRunningScene()->removeChild(bagImage);
    }
    bagImage->setVisible(!isVisible);
   
    /*if (items.empty()) {
        return;
    }
    float xOffset = (Director::getInstance()->getVisibleSize().width) * 0.24; // Start X offset for items
    float yOffset = (Director::getInstance()->getVisibleSize().height) / 3 * 2.12; // Start Y offset for items
    float Xgap = (Director::getInstance()->getVisibleSize().width) * 0.047;
    float Ygap = (Director::getInstance()->getVisibleSize().height) * 0.098;
    for (int count = 0; count < items.size();) {
        items[count].display(xOffset, yOffset, false);  // Display each item, you may want to set its position too
        xOffset += Xgap;
        count++;
        if (count % 12 == 0) {
            yOffset -= Ygap;
            xOffset = (Director::getInstance()->getVisibleSize().width) * 0.24;
        }
    }*/
}
   




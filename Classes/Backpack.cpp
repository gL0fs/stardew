#include "Backpack.h"

USING_NS_CC;

// Constructor to initialize Item with name and quantity

Item::Item(const std::string& itemName, int itemQuantity) 
    : name(itemName), quantity(itemQuantity) {

    text = ui::Text::create(std::to_string(quantity), "fonts/Marker Felt.ttf", 8);
    if (text) {
        text->setAnchorPoint(Vec2(-0.3, 1.3)); 
        text->setVisible(false);
        text->retain();
    }

    std::string png_name = name + ".png";
    itemImage = ui::ImageView::create(png_name);
    if (itemImage) {
        itemImage->setScale(2); 
        itemImage->setVisible(false);
        itemImage->retain();
    }
}

// Function to display item information
void Item::display(float x, float y, int size) const {
    
    Vec2 position(x, y);
    
    // 创建一个 Label 显示物品名称和数量
    if (quantity != 1 && text) { 
        bool TextisVisible = text->isVisible();
        if (!TextisVisible) {
            text->setFontSize(8*size/2);
            text->setPosition(position);
            Director::getInstance()->getRunningScene()->addChild(text);
        }
        else {
            Director::getInstance()->getRunningScene()->removeChild(text);
        }
        text->setVisible(!TextisVisible);
    }
    if (itemImage) {
        bool ImageisVisible = itemImage->isVisible();
        if (!ImageisVisible) {        
            // 设置标签的显示位置
            itemImage->setScale(size);
            itemImage->setPosition(position); // 使用传入的 x, y 作为位置
            // 将标签添加到父节点（ui 层）
            Director::getInstance()->getRunningScene()->addChild(itemImage);
        }
        else {
            Director::getInstance()->getRunningScene()->removeChild(itemImage);
        }
        itemImage->setVisible(!ImageisVisible);
    }
}


Inventory::Inventory(size_t c) : capacity(c), items(), currentIndex(0){
    items.reserve(c);

    bagImage = ui::ImageView::create("bag.png");
    bagImage->retain();
    if (bagImage) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        // 计算屏幕中央的坐标
        Vec2 centerPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30);  // 根据需要调整Y偏移
        // 设置 bagImage 的位置为视图中央
        bagImage->setPosition(centerPosition);
        bagImage->setScale(0.8);
        bagImage->setVisible(false);
        bagImage->retain();
    }
}

Inventory::~Inventory()
{
    
}

bool Inventory::isOpen() {
    if (bagImage->isVisible()) {
        return true;
    }
    return false;
}

bool Inventory::removeItem(const std::string& name, int quantity) {
    if (isOpen()) {
        items_display();
    }
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->name == name) {
            if (it->quantity >= quantity) {
                it->quantity -= quantity;
                if (it->quantity == 0) {
                    items.erase(it);
                }
                if (isOpen()) {
                    items_display();
                }
                return true;
            }
            else {
                CCLOG("Not enough %s to remove.", name.c_str());
                return false;
            }
        }
    }
    if (isOpen()) {
        items_display();
    }
    return false;
}

bool Inventory::addItemToInventory(const std::string& name, int quantity) {
    if (isOpen()) {
        items_display();
    }
    if (!items.empty() && name.substr(0,4) != "tool") {
        for (auto& item : items) {
            if (item.name == name) {
                item.quantity += quantity;
                if (isOpen()) {
                    items_display();
                }
                return true;
            }
        }
        if (items.size() >= capacity) {
            CCLOG("Inventory is full! Cannot add %s.", name.c_str());
            return false;
        }
    }
    items.emplace_back(name, quantity);
    if (isOpen()) {
        items_display();
    }
    return true;
}

std::vector<Item> Inventory::getItems() {
    return items;
}


void Inventory::items_display(size_t currentIndex) const {
    float xOffset = (Director::getInstance()->getVisibleSize().width) * 0.24; // Start X offset for items
    float yOffset = (Director::getInstance()->getVisibleSize().height) / 3 * 2.12; // Start Y offset for items
    const float Xgap = (Director::getInstance()->getVisibleSize().width) * 0.047;
    const float Ygap = (Director::getInstance()->getVisibleSize().height) * 0.098;
    for (int count = 0; count < items.size();) {
        items[count].text->setString(std::to_string(items[count].quantity));
        if(count== currentIndex)items[count].display(xOffset, yOffset, 3);  // Display each item, you may want to set its position too
        else items[count].display(xOffset, yOffset);
        xOffset += Xgap;
        count++;
        if (count % 12 == 0) {
            yOffset -= Ygap;
            xOffset = (Director::getInstance()->getVisibleSize().width) * 0.24;
        }
    }
}

void Inventory::displayInventory()const {
    const bool isVisible = bagImage->isVisible();
    if (!isVisible) {
        Director::getInstance()->getRunningScene()->addChild(bagImage);   
    }
    else {
        Director::getInstance()->getRunningScene()->removeChild(bagImage);
    }
    bagImage->setVisible(!isVisible);
   
    if (items.empty()) {
        return;
    }
    items_display();    
}
   

void Inventory::updateSelectedItem(cocos2d::EventMouse* e) {
    if (e) {
        float scrollY = e->getScrollY();

        // 根据滚轮方向调整当前物品索引
        if (scrollY > 0) {  // 向上滚动
            if (currentIndex > 0) {
                currentIndex--;
            }
        }
        else {  // 向下滚动
            if (currentIndex < items.size() - 1) {
                currentIndex++;
            }
        }

        // 在控制台输出选中的物品名称
        CCLOG("Selected Item: %s", items[currentIndex].name.c_str());

        // 更新显示选中的物品
        items_display(currentIndex);
        items_display(currentIndex);
    } 
}

Item Inventory::getSelectedItem() const {
    return items[currentIndex];  // 返回当前选中的物品
}



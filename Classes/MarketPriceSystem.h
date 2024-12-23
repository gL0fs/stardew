#ifndef MARKET_PRICE_SYSTEM_H
#define MARKET_PRICE_SYSTEM_H

#include <map>
#include <string>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <unordered_map> // 用于记录销量

class MarketPriceSystem {
public:
    // 获取单例实例
    static MarketPriceSystem& getInstance() {
        static MarketPriceSystem instance; // 静态局部变量，保证单例
        return instance;
    }

    // 获取商品价格
    int getPrice(const std::string& itemName) const {
        auto it = prices.find(itemName);
        if (it != prices.end()) {
            return it->second;
        }
        return 0; // 默认价格为 0
    }

    // 促销函数：随机调整商品价格
    void applyPromotion() {
        for (auto& item : prices) {
            int discount = rand() % 20; // 价格在0 到 +20 之间波动
            item.second += discount;
            if (item.second < 1) item.second = 1; // 确保价格不为负数
        }
    }

    // 价格更新函数：根据销量调整商品价格
    void updatePricesBasedOnSales() {
        for (const auto& sale : sales) {
            const std::string& itemName = sale.first;
            int quantitySold = sale.second;
            if (quantitySold > 0) {
                auto it = prices.find(itemName);
                if (it != prices.end()) {
                    // 根据物品类型调整价格
                    if (itemName == "food1") {
                        it->second -= quantitySold / 4; // 每卖出 4 个，价格降低 1
                    }
                    else if (itemName == "food2") {
                        it->second -= quantitySold / 2; // 每卖出 2 个，价格降低 1
                    }
                    else if (itemName == "food3") {
                        it->second -= quantitySold; // 每卖出 1 个，价格降低 1
                    }
                    else {
                        it->second -= quantitySold / 2; // 其他物品每卖出 2 个，价格降低 1
                    }
                    if (it->second < 1) it->second = 1; // 确保价格不为负数
                }
            }
        }
        
    }

    void resetPricesWithVariation() {
        // 重置为初始价格
        initializePrices();
        sales.clear(); // 清空销量记录
        // 添加小幅度随机变化
        for (auto& item : prices) {
            int variation = rand() % 6 - 3; // 价格在 -3 到 +3 之间波动
            item.second += variation;
            if (item.second < 1) item.second = 1; // 确保价格不为负数
        }
    }

    // 记录商品销量
    void recordSale(const std::string& itemName, int quantity) {
        sales[itemName] += quantity;
    }

    // 打印所有商品价格（用于调试）
    void printPrices() const {
        for (const auto& item : prices) {
            printf("%s: %d coins\n", item.first.c_str(), item.second);
        }
    }

    // 初始化商品价格
    void initializePrices() {
        prices["flower"] = 30;
        prices["plant"] = 30;
        prices["wood"] = 10;
        prices["berry"] = 30;
        prices["fish1"] = 10;
        prices["fish2"] = 30;
        prices["fish3"] = 50;
        prices["kuang1"] = 50;
        prices["kuang2"] = 10;
        prices["kuang3"] = 10;
        prices["carrot3"] = 30;
        prices["egg"] = 30;
        prices["cow"] = 40;
        prices["redflower3"] = 60;   // 新商品 redflower3，价格为 60
        prices["smalltree3"] = 120;  // 新商品 smalltree3，价格为 120

        // 新增 food1, food2, food3 的价格
        prices["food1"] = 20;
        prices["food2"] = 60;
        prices["food3"] = 150;
    }

private:
    // 构造函数（私有化，防止外部实例化）
    MarketPriceSystem() {
        initializePrices();
        srand(static_cast<unsigned int>(time(nullptr))); // 初始化随机种子
    }

    // 禁止拷贝构造和赋值操作
    MarketPriceSystem(const MarketPriceSystem&) = delete;
    MarketPriceSystem& operator=(const MarketPriceSystem&) = delete;

    std::map<std::string, int> prices; // 商品名称 -> 价格
    std::unordered_map<std::string, int> sales; // 商品名称 -> 销量
};

#endif // MARKET_PRICE_SYSTEM_H
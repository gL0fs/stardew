#ifndef MARKET_PRICE_SYSTEM_H
#define MARKET_PRICE_SYSTEM_H

#include <map>
#include <string>
#include <cstdlib> // for rand()
#include <ctime>   // for time()

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

    // 更新商品价格（可以动态调整）
    void updatePrices() {
        for (auto& item : prices) {
            item.second += rand() % 10 - 5; // 价格在 -5 到 +5 之间波动
            if (item.second < 1) item.second = 1; // 确保价格不为负数
        }
    }

    // 打印所有商品价格（用于调试）
    void printPrices() const {
        for (const auto& item : prices) {
            printf("%s: %d coins\n", item.first.c_str(), item.second);
        }
    }
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
        prices["crop2"] = 60;
        prices["crop3"] = 100;
        prices["egg"] = 30;
        prices["cow"] = 40;
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
};

#endif // MARKET_PRICE_SYSTEM_H
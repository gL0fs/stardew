#ifndef MARKET_PRICE_SYSTEM_H
#define MARKET_PRICE_SYSTEM_H

#include <map>
#include <string>
#include <cstdlib> // for rand()
#include <ctime>   // for time()

class MarketPriceSystem {
public:
    // ��ȡ����ʵ��
    static MarketPriceSystem& getInstance() {
        static MarketPriceSystem instance; // ��̬�ֲ���������֤����
        return instance;
    }

    // ��ȡ��Ʒ�۸�
    int getPrice(const std::string& itemName) const {
        auto it = prices.find(itemName);
        if (it != prices.end()) {
            return it->second;
        }
        return 0; // Ĭ�ϼ۸�Ϊ 0
    }

    // ������Ʒ�۸񣨿��Զ�̬������
    void updatePrices() {
        for (auto& item : prices) {
            item.second += rand() % 10 - 5; // �۸��� -5 �� +5 ֮�䲨��
            if (item.second < 1) item.second = 1; // ȷ���۸�Ϊ����
        }
    }

    // ��ӡ������Ʒ�۸����ڵ��ԣ�
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
    // ���캯����˽�л�����ֹ�ⲿʵ������
    MarketPriceSystem() {
        initializePrices();
        srand(static_cast<unsigned int>(time(nullptr))); // ��ʼ���������
    }

    // ��ֹ��������͸�ֵ����
    MarketPriceSystem(const MarketPriceSystem&) = delete;
    MarketPriceSystem& operator=(const MarketPriceSystem&) = delete;



    std::map<std::string, int> prices; // ��Ʒ���� -> �۸�
};

#endif // MARKET_PRICE_SYSTEM_H
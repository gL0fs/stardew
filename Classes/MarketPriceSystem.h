#ifndef MARKET_PRICE_SYSTEM_H
#define MARKET_PRICE_SYSTEM_H

#include <map>
#include <string>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <unordered_map> // ���ڼ�¼����

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

    // �������������������Ʒ�۸�
    void applyPromotion() {
        for (auto& item : prices) {
            int discount = rand() % 20 ; // �۸���0 �� +20 ֮�䲨��
            item.second += discount;
            if (item.second < 1) item.second = 1; // ȷ���۸�Ϊ����
        }
    }

    // �۸���º�������������������Ʒ�۸�
    void updatePricesBasedOnSales() {
        for (const auto& sale : sales) {
            const std::string& itemName = sale.first;
            int quantitySold = sale.second;
            if (quantitySold > 0) {
                auto it = prices.find(itemName);
                if (it != prices.end()) {
                    it->second -= quantitySold / 2; // ÿ���� 2�����۸񽵵� 1
                    if (it->second < 1) it->second = 1; // ȷ���۸�Ϊ����
                }
            }
        }
       //sales.clear(); // ���������¼
    }
    void resetPricesWithVariation() {
        // ����Ϊ��ʼ�۸�
        initializePrices();
        sales.clear(); // ���������¼
        // ���С��������仯
        for (auto& item : prices) {
            int variation = rand() % 6 - 3; // �۸��� -3 �� +3 ֮�䲨��
            item.second += variation;
            if (item.second < 1) item.second = 1; // ȷ���۸�Ϊ����
        }
    }

    // ��¼��Ʒ����
    void recordSale(const std::string& itemName, int quantity) {
        sales[itemName] += quantity;
    }

    // ��ӡ������Ʒ�۸����ڵ��ԣ�
    void printPrices() const {
        for (const auto& item : prices) {
            printf("%s: %d coins\n", item.first.c_str(), item.second);
        }
    }

    // ��ʼ����Ʒ�۸�
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
        prices["redflower3"] = 60;   // ����Ʒ redflower3���۸�Ϊ 60
        prices["smalltree3"] = 120;  // ����Ʒ smalltree3���۸�Ϊ 120
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
    std::unordered_map<std::string, int> sales; // ��Ʒ���� -> ����
};

#endif // MARKET_PRICE_SYSTEM_H
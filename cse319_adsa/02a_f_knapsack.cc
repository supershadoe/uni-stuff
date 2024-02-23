#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <functional>

class Item {
    public:
        float profit, weight, pw_ratio;
        Item(float p, float w): profit(p), weight(w), pw_ratio(p/w) {}
        
        Item(const Item& other, int c) {
            profit = other.profit * (c / other.weight);
            weight = c;
            pw_ratio = profit / weight;
        }

        friend bool operator > (const Item& a, const Item& b) {
            return a.pw_ratio > b.pw_ratio;
        }
};

class Knapsack {
    private:
        int n, cap;
        std::vector<Item> obj, sel_obj;
    public:
        Knapsack() {
            std::cout << "Enter the number of objects: ";
            std::cin >> n;

            if (n < 1)
                throw std::length_error("Cannot have length less than one.");

            for (int i = 0; i < n; i++) {
                float p, w;
                std::cout << "Enter profit and weight of object " << i + 1 << ": ";
                if (p < 0 || w < 0)
                    throw std::domain_error("How can profit/weight be zero?");
                std::cin >> p >> w;
                obj.push_back(Item(p, w));
            }

            std::cout << "Enter the capacity of the bag: ";
            std::cin >> cap;

            if (cap <= 0)
                throw std::domain_error("Capacity of the bag can't be zero or less.");
        }

        void max_profit() {
            float c = cap, i = 0;
            std::sort(obj.begin(), obj.end(), std::greater<Item>());

            while (c > 0 && i < n) {
                if (obj[i].weight <= c) {
                    sel_obj.push_back(obj[i]);
                    c -= obj[i].weight;
                } else {
                    sel_obj.push_back(Item(obj[i], c));
                    c = 0;
                }
                i++;
            }
        }

        void show_sel_obj() {
            using namespace std;
            float p = 0;
            cout << "Profit - Weight - p/w" << endl;
            for (std::vector<Item>::iterator obj = sel_obj.begin(); obj != sel_obj.end(); obj++) {
                p += obj->profit;
                cout << obj->profit << " - " << obj->weight << " - " << obj->pw_ratio << endl;
            }
            cout << "Max profit: " << p << endl;
        }
};

int main() {
    Knapsack k;
    k.max_profit();
    k.show_sel_obj();
    return 0;
}


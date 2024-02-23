#include <iostream>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <limits>

class RodCutter {
    private:
        std::map<int, int> profit_memo;
        int *prices, n;

        int _max_profit_td(int n) {
            int max_profit = 0, t;
            if (n == 0) return 0;
            for (int i = 1; i <= n; i++) {
                try {
                    t = profit_memo.at(n - i);
                } catch(std::out_of_range e) {
                    t = _max_profit_td(n - i);
                    profit_memo[n - i] = t;
                }
                t += prices[i - 1];
                max_profit = std::max(max_profit, t);
            }
            return max_profit;
        }

        int _max_profit_bu() {
            auto *r = new int[n + 1];
            r[0] = 0;

            for (auto i = 1; i <= n; i++) {
                auto max_profit = std::numeric_limits<int>::min();
                for (auto j = 0; j < i; j++)
                    max_profit = std::max(
                        max_profit, prices[j] + r[(i - 1) - j]
                    );
                r[i] = max_profit;
            }

            return r[n];
        }
    public:
        RodCutter() {
            std::cout << "Enter the number of rods: ";
            std::cin >> n;

            if (n < 1)
                throw std::out_of_range("Array count can't be less than 1");

            prices = new int[n];

            std::cout << "Enter the price list: ";
            for (int i = 0; i < n; i++)
                std::cin >> prices[i];
        }

        int get_n() { return n; }

        int cut_rods() { return _max_profit_td(n); }

        ~RodCutter() {
            delete prices;
        }
};

int main() {
    RodCutter cutter;
    std::cout << "Max profit for " << cutter.get_n()
        << " rods is " << cutter.cut_rods() << std::endl;
    return 0;
}

#include <iostream>
#include <algorithm>
#include <vector>

class TSP {
private:
    int n, **cost;
public:
    TSP(int n) {
        std::cout << "Enter the cost between cities as a matrix." << std::endl;
        this->n = n;
        cost = new int*[n];
        for (int i = 0; i < n; i++) {
            cost[i] = new int[n];
            for (int j = 0; j < n; j++) {
                std::cin >> cost[i][j];
            }
        }
    }
    
    ~TSP() {
        for (int i = 0; i < n; i++) {
            delete cost[i];
        }
        delete cost;
    }
    
    void solve_heuristic(int s) {
        int* trip = new int[n-1];
        std::vector<int> vertex;
        for (int i = 0; i < n; i++) {
            if (i == s) continue;
            vertex.push_back(i);
        }
        
        int min_path = -1;
        
        while (std::next_permutation(vertex.begin(), vertex.end())) {
            int cur_path = 0, k = s;
            for (int i = 0; i < n - 1; i++) {
                cur_path += cost[k][vertex[i]];
                k = vertex[i];
            }
            cur_path += cost[k][s];

            if (cur_path < min_path || min_path == -1) {
                for (int i = 0; i < n - 1; i++) {
                    trip[i] = vertex[i];
                }
                min_path = cur_path;
            }
        }

        std::cout << "The shortest possible trip to visit every city is: " << s + 1 << " ";
        for (int i = 0; i < n - 1; i++) {
            std::cout << trip[i] + 1 << " ";
        }
        std::cout << s + 1 << "\nwith a cost of " << min_path << std::endl;

        delete trip;
    }
};

int main() {
    int n;
    std::cout << "Enter the number of cities: ";
    std::cin >> n;
    TSP tsp(n);
    std::cout << "Enter the starting vertex: ";
    std::cin >> n;
    n--;
    tsp.solve_heuristic(n);
    return 0;
}

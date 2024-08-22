#include <iostream>
#define LARGE_DIST 32767

class FloydWarshall {
private:
    const int n;
    int **graph, **d, **p;

    void display(int **a) const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                std::cout << a[i][j] << "\t";
            std::cout << "\n";
        }
    }
public:
    FloydWarshall(int m): n(m) {
        std::cout << "Enter the distance matrix of the graph:" << std::endl;
        graph = new int*[n];
        d = new int*[n];
        p = new int*[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new int[n];
            d[i] = new int[n];
            p[i] = new int[n];
            for (int j = 0; j < n; j++)
                std::cin >> graph[i][j];
        }
    }

    ~FloydWarshall() {
        for (int i = 0; i < n; i++) {
            delete graph[i];
            delete d[i];
            delete p[i];
        }
        delete graph;
        delete d;
        delete p;
    }

    void solve() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = graph[i][j];
                p[i][j] = i == j || d[i][j] == LARGE_DIST ? -1 : i;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) {
                    if (j == i || k == i) continue;
                    int dist = d[j][i] + d[i][k];
                    if (dist < d[j][k]) {
                        d[j][k] = dist;
                        p[j][k] = p[i][k];
                    }
                }
        }
        std::cout << "D(" << n << ")" << "\n";
        display(d);
        std::cout << "P(" << n << ")" << "\n";
        display(p);
    }
};

int main() {
    int n;
    std::cout << "Enter the number of vertices: ";
    std::cin >> n;

    if (n < 1) {
        std::cerr << "Number of vertices can't less than 1.\n";
        return 1;
    }

    FloydWarshall f(n);
    f.solve();

    return 0;
}

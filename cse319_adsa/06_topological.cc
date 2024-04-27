#include <iostream>
#include <list>
#include <vector>

struct Vertex {
    char value;
    bool visited;
    int parent;
    int finish;
    std::list<int> adj;

    Vertex(char val, std::list<int>& a):
        value(val), visited(false), parent(-1), finish(-1), adj(a) {}
};

class TopologicalSort {
    std::vector<Vertex> &graph;
    int clock;
    std::list<int> sort;

    void dfs_visit(int u) {
        clock++;
        std::list<int> *adj = &(graph[u].adj);
        for (std::list<int>::iterator i = (*adj).begin(); i != (*adj).end(); i++)
            if (!graph[*i].visited) {
                graph[*i].parent = u;
                dfs_visit(*i);
            }
        graph[u].visited = true;
        clock++;
        graph[u].finish = clock;
        sort.push_front(u);
    }

    void dfs() {
        for (int i = 0; i < graph.size(); i++) {
            graph[i].visited = false;
            graph[i].parent = -1;
            graph[i].finish = -1;
        }
        for (int i = 0; i < graph.size(); i++)
            if (!graph[i].visited)
                dfs_visit(i);
    }
public:
    TopologicalSort(std::vector<Vertex> &g): graph(g), clock(0) {}

    void solve() {
        using namespace std;
        dfs();
        
        cout << "Vertex val\tParent\tVisited\tFinish time\n";
        for (std::vector<Vertex>::iterator vertex = graph.begin(); vertex != graph.end(); vertex++) {
            cout << vertex->value << "\t\t"
                << (vertex->parent < 0 ? "NULL" : "")
                << (vertex->parent < 0 ? '\0' : graph[vertex->parent].value) << "\t"
                << (vertex->visited ? "True" : "False") << "\t"
                << vertex->finish << "\n";
        }

        cout << "The topological order is: ";
        for (std::list<int>::iterator i = sort.begin(); i != sort.end(); i++) {
            cout << graph[*i].value << " ";
        }
        cout << endl;
    }
};

int main() {
    using namespace std;
    int n;
    vector<Vertex> graph;

    cout << "Enter the number of vertices: ";
    cin >> n;

    if (n < 1) {
        cerr << "Graph cannot exist without any vertices.\n";
        return 1;
    }

    cout << "Value | Adj count | Adj list (indices, split by space)" << endl;
    for (int i = 0; i < n; i++) {
        char val;
        int count;
        list<int> adj;
        cin >> val >> count;
        for (int j = 0; j < count; j++) {
            int ind;
            cin >> ind;
            adj.push_back(ind);
        }
        graph.push_back(Vertex(val, adj));
    }

    TopologicalSort t(graph);
    t.solve();

    return 0;
}

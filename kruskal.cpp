#include <bits/stdc++.h>
using namespace std;

// Class cạnh để biểu diễn cạnh
class Edge {
    public:
        int u, v;
        double w;

    Edge(int u, int v, double w) {
        this->u = u;
        this->v = v;
        this->w = w;
    }
};

vector<Edge*> edges;
vector<int> parent;
int n;

// Xử lí input
void input() {
    fstream fi("Graph.txt");
    fi >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            double w; fi >> w;
            if(j <= i) continue;

            if(w > 0) {
                Edge* edge = new Edge(i, j, w);
                edges.push_back(edge);
            }
            
        }
    }
    fi.close();
}

// Sort các cạnh tăng dần theo weight
bool myCmp(Edge* a, Edge* b) {
    return a->w < b->w;
}

// Ba hàm của DSU - Disjoint Set Union
void make_set() {
    for(int i = 0; i < n; i++) {
        parent.push_back(i);
    }
}

// Tìm "cha" của một phần tử, hay có thể hiểu là check xem phần tử đang thuộc tập hợp nào
int find(int x) {
    if(x == parent[x]) return x;
    else return find(parent[x]);
}

// Kiểm tra có thể nối phần tử này vào tập hợp kia được không
bool isUnion(int u, int v) {
    u = find(u);
    v = find(v);

    // Nếu hai phần tử cùng "cha" - cùng thuộc 1 tập hợp thì sẽ không nối vì sẽ tạo ra chu trình
    if(u == v) return false;
    else return true;
}

// Thuật toán Kruskal
void kruskal() {
    fstream fo("Kruskal.txt", ios::out);
    vector<Edge*> tree;
    double totalWeight = 0;
    sort(edges.begin(), edges.end(), myCmp);
    for(int i = 0; i < n; i++) {
        auto edge = edges[i];
        if(isUnion(edge->u, edge->v)) {
            totalWeight += edge->w;
            tree.push_back(edge);
        }
        // Nếu đủ n - 1 cạnh thì dừng
        if(tree.size() == n - 1) break;
    }
    fo << round(totalWeight * 100)/100 << endl;
    fo.close();
}

int main() {
    input();
    make_set();
    kruskal();
}

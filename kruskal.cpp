#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

class DisjointSet {
public:
    DisjointSet(int size) {
        parent.resize(size);
        rank.resize(size);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void merge(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (rank[px] < rank[py]) {
            parent[px] = py;
        }
        else if (rank[px] > rank[py]) {
            parent[py] = px;
        }
        else {
            parent[px] = py;
            rank[py]++;
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }

    sort(edges.begin(), edges.end(), compareEdges);

    DisjointSet ds(n);
    vector<Edge> mst_min;
    vector<Edge> mst_max;
    int mst_min_weight = 0;
    int mst_max_weight = 0;

    for (int i = 0; i < m; i++) {
        Edge e = edges[i];
        if (ds.find(e.from) != ds.find(e.to)) {
            ds.merge(e.from, e.to);
            mst_min.push_back(e);
            mst_min_weight += e.weight;
        }
    }

    ds = DisjointSet(n);
    reverse(edges.begin(), edges.end());
    for (int i = 0; i < m; i++) {
        Edge e = edges[i];
        if (ds.find(e.from) != ds.find(e.to)) {
            ds.merge(e.from, e.to);
            mst_max.push_back(e);
            mst_max_weight += e.weight;
        }
    }

    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 0; i < mst_min.size(); i++) {
        cout << mst_min[i].from << " " << mst_min[i].to << " " << mst_min[i].weight << endl;
    }
    cout << "Weight: " << mst_min_weight << endl;

    cout << "Maximum Spanning Tree:" << endl;
    for (int i = 0; i < mst_max.size(); i++) {
        cout << mst_max[i].from << " " << mst_max[i].to << " " << mst_max[i].weight << endl;
    }
    cout << "Weight: " << mst_max_weight << endl;

    int diff = mst_max_weight - mst_min_weight;
    cout << "Difference: " << diff << endl;

    return 0;
}

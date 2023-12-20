#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
const int MAXN = 1e5 + 10;

// union_find 
struct ds_set {
    int fa[MAXN];

    ds_set()        { for (int i = 1;i <= MAXN;i ++) fa[i] = i; }
    int find(int x) { return (fa[x] == x) ? x : fa[x] = find(fa[x]); }
    int check(int x, int y) { return find(x) == find(y); }
    void merge(int x, int y) {
        int u = find(x), v = find(y);
        if ( u != v ) {
            fa[u] = v;
        }
    }
};
///////////////

struct Node {
    int u, v, w;
};
vector<Node>g;

#define NOT_FOUND -0x3f3f3f3f
int kruskal(int n) {
    int res = 0, cnt = 0;
    ds_set d;

    sort(g.begin(), g.end(), [](Node a, Node b) { return a.w < b.w; } );

    for (auto x : g) {
        if ( !d.check(x.u, x.v) ) {
            res += x.w;
            d.merge(x.v, x.u);
            cnt ++;
        }
    }
    return (cnt == n - 1) ? res : NOT_FOUND;
}

int main() {
    int n, m;
    cin >> n >> m;
    while ( m -- ) {
        int u, v, w;
        cin >> u >> v >> w;
        g.push_back({u, v, w});
        g.push_back({v, u, w});
    }

    int res = kruskal(n);
    if ( res == NOT_FOUND ) { 
        cout << "impossible\n";
    }
    else {
        cout << res << "\n";
    }
    return 0;
}
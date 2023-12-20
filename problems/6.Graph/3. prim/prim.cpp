#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> PII;
const int MAXN = 510;
vector<PII>g[MAXN];

#define NOT_FOUND -0x3f3f3f3f
int prim(int n) {
    int vis[n + 1] = {0};
    priority_queue<PII, vector<PII>, greater<PII>>q;
    q.push({0, 1});

    int res = 0, cnt = 0;
    while ( !q.empty() ) {
        int w = q.top().first, v = q.top().second;
        q.pop();

        if ( vis[v] ) continue;
        vis[v] = 1;

        cnt ++;
        res += w;
        
        for (auto x : g[v]) {
            q.push(x);
        }
    }

    return (cnt == n) ? res : NOT_FOUND;
}

int main() {
    int n, m;
    cin >> n >> m;

    while ( m -- ) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({w, v});
        g[v].push_back({w, u});
    }

    int res = prim(n);
    if ( res == NOT_FOUND ) {
        cout << "impossible";
    }
    else {
        cout << res;
    }
    cout << "\n";
    return 0;
}
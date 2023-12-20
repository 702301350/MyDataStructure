#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f;
const int MAXN = 2e5 + 10;
vector<PII>g[MAXN]; // {edge vertex}
int vis[MAXN], dis[MAXN];

int dijsktra(int n) {
    memset(dis, INF, sizeof dis);
    priority_queue<PII, vector<PII>, greater<PII>>q;
    dis[1] = 0;
    q.push({0, 1});
    
    while ( !q.empty() ) {
        int w = q.top().first, v = q.top().second;
        q.pop();
        
        if ( vis[v] ) continue;
        vis[v] = 1;
        
        for (auto x : g[v]) {
            int to_w = x.first, to_v = x.second;
            if ( dis[to_v] > dis[v] + to_w ) {
                dis[to_v] = dis[v] + to_w;
                q.push({dis[to_v], to_v});
            }
        }
    }
    
    return (dis[n] == INF) ? -1 : dis[n];
}

int main() {
    int n, m, x, y, z;
    cin >> n >> m;
    
    while ( m -- ) {
        cin >> x >> y >> z;
        g[x].push_back({z, y});
    }
    
    cout << dijsktra(n);
    return 0;
}
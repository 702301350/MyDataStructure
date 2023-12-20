#include <iostream>
#include <cstring>
using namespace std;

const int INF  = 0x3f3f3f3f;
const int MAXN = 1010;
int g[MAXN][MAXN], dis[MAXN], vis[MAXN];

int dijkstra(int n) {
    memset(dis, INF, sizeof dis);

    dis[1] = 0;

    for (int i = 0;i < n;i ++) {
        int t = -1;
        for (int j = 1;j <= n;j ++) {
            if ( !vis[j] && (t == -1 || dis[t] > dis[j]) ) {
                t = j;
            }
        }

        if ( t == n ) break;

        vis[t] = 1;

        for (int j = 1;j <= n;j ++) {
            dis[j] = min(dis[j], dis[t] + g[t][j]);
        }
    }
    return (dis[n] != INF) ? dis[n] : -1;
}

int main() {
    int n, m, x, y, z;
    cin >> n >> m;
    memset(g, INF, sizeof g);
    while ( m -- ) {
        cin >> x >> y >> z;
        g[x][y] = min(g[x][y], z);
    }
    cout << dijkstra(n);
    return 0;
}
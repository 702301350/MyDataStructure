#include <iostream>
#include <cstring>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 210;
int dp[MAXN][MAXN], g[MAXN][MAXN];

void floyd(int n) {
    for (int i = 1;i <= n;i ++) dp[i][i] = 0;
    for (int k = 1;k <= n;k ++) {
        for (int i = 1;i <= n;i ++) {
            for (int j = 1;j <= n;j ++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    memset(dp, INF, sizeof dp);
    while ( m -- ) {
        int a, b, c;
        cin >> a >> b >> c;
        dp[a][b] = min(dp[a][b], c);
    }

    floyd(n);

    while ( k -- ) {
        int a, b;
        cin >> a >> b;
        if ( dp[a][b] <= INF / 2 ) {
            cout << dp[a][b];
        }
        else {
            cout << "impossible";
        }
        cout << "\n";
    }
    return 0;
}
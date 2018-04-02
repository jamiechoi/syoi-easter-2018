#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int jump[2][1001][1001];
int cur[1001][1001];
int pres[1001][1001];
int n, m, q, t;

int main() {
  cin >> n >> m >> q >> t;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> pres[i][j];
      cur[i][j] = jump[0][i][j] = i * 10000 + j;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int ans = pres[i][j];
      for (int k = 0; k < 4; k++) {
        int ni = i + dx[k], nj = j + dy[k];
        if (ni >= 1 && ni <= n && nj >= 1 && nj <= m) {
          if (pres[ni][nj] > ans) {
            ans = pres[ni][nj];
            jump[0][i][j] = ni * 10000 + nj;
          }
        }
      }
    }
  }
  int s = 0;
  while (t) {
    if (t & 1) {
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
          int ni = cur[i][j] / 10000, nj = cur[i][j] % 10000;
          cur[i][j] = jump[s][ni][nj];
        }
    }

    t >>= 1;

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        int ni = jump[s][i][j] / 10000, nj = jump[s][i][j] % 10000;
        jump[!s][i][j] = jump[s][ni][nj];
      }
    s = !s;
  }
  for (int i = 0; i < q; i++) {
    int a, b;
    cin >> a >> b;
    cout << (cur[a][b] / 10000) << " " << (cur[a][b] % 10000) << endl;
  }
}
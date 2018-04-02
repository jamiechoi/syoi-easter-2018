#include <bits/stdc++.h>
using namespace std;

typedef pair<int, pair<int, int>> edge;
typedef long long ll;

ll n, q, ans[100005][2], cost[1000005];
int mp[805][805], p[1000005];
pair<int, int> u[100005];
vector<edge> v, v2;

int iabs(int x) { return x > 0 ? x : -x; }

void init() {
  for (int i = 0; i < 1000005; i++)
    p[i] = i;
}

int find(int n) {
  if (p[n] == n)
    return n;
  else
    return p[n] = find(p[n]);
}

int main() {
  cin >> n >> q;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> mp[i][j];
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n; j++) {
      v.push_back(
          {iabs(mp[i + 1][j] - mp[i][j]), {i * 1000 + j, (i + 1) * 1000 + j}});
      v.push_back(
          {iabs(mp[j][i + 1] - mp[j][i]), {j * 1000 + i, j * 1000 + i + 1}});
    }
  sort(v.begin(), v.end());
  init();
  for (auto e : v) {
    int a = e.second.first, b = e.second.second;
    if (find(a) != find(b)) {
      p[find(a)] = find(b);
      v2.push_back(e);
    }
  }
  for (int i = 0; i < q; i++)
    u[i].second = i, cin >> u[i].first;
  sort(u, u + q);
  init();
  ll t = 0, mx = 0;
  for (int i = 0; i < q; i++) {
    int x = u[i].first, y = u[i].second;
    while (t < v2.size() && v2[t].first <= x) {
      int a = v2[t].second.first, b = v2[t].second.second;
      if (find(a) != find(b)) {
        cost[find(a)] += cost[find(b)] + v2[t].first;
        p[find(b)] = find(a);
        mx = max(mx, cost[find(a)]);
      }
      t++;
    }
    ans[y][0] = v2.size() - t + 1;
    ans[y][1] = mx;
  }
  for (int i = 0; i < q; i++) {
    cout << ans[i][0] << " " << ans[i][1] << endl;
  }
  return 0;
}
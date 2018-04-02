#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int log2t[10005];
vector<pair<int, int>> g[10005];
int up[15][10005];
ll dist[15][10005];
int depth[10005];

// calculate log2[t] for 1 <= t < 10005
void init() {
  log2t[0] = -1;
  for (int i = 0; i < 31; i++) {
    for (int j = (1 << i); j < (1 << i + 1) && j < 10005; j++)
      log2t[j] = i;
  }
}

// DFS to build the graph
void dfs(int n, int p = -1, int len = 0, int dep = 0) {
  up[0][n] = p;
  dist[0][n] = len;
  depth[n] = dep;
  for (auto h : g[n])
    if (h.first != p)
      dfs(h.first, n, h.second, dep + 1);
}

// the d-th ancestor of u
int upf(int u, int d) {
  for (int i = 0; d; i++) {
    if (d & (1 << i)) {
      u = up[i][u];
      d &= ~(1 << i);
    }
  }
  return u;
}

// l: LCA of u and v
// du: distance between u and l
// dv: distance between v and l
void lca(int u, int v, int &l, int &du, int &dv) {
  int u0 = u, v0 = v;
  du = 0, dv = 0;

  // raise to the same level
  if (depth[u] < depth[v]) {
    dv += depth[v] - depth[u];
    v = upf(v, depth[v] - depth[u]);
  } else {
    du += depth[u] - depth[v];
    u = upf(u, depth[u] - depth[v]);
  }

  if (u == v) {
    l = u;
    return;
  }

  for (int i = log2t[depth[u]]; i >= 0; i--) {
    if (up[i][u] != up[i][v]) {
      u = up[i][u], v = up[i][v];
      du += 1 << i;
      dv += 1 << i;
    }
  }

  du++;
  dv++;
  l = up[0][u];
}

// Query DIST u v
ll distf(int u, int v) {
  int l, du, dv;
  ll ans = 0;
  lca(u, v, l, du, dv);
  for (int i = log2t[du]; i >= 0; i--) {
    if (du & (1 << i)) {
      ans += dist[i][u];
      u = up[i][u];
    }
  }
  for (int i = log2t[dv]; i >= 0; i--) {
    if (dv & (1 << i)) {
      ans += dist[i][v];
      v = up[i][v];
    }
  }
  return ans;
}

// Query KTH u v k
int kth(int u, int v, int k) {
  int l, du, dv;

  lca(u, v, l, du, dv);
  k--;
  if (k <= du) {
    return upf(u, k);
  } else {
    return upf(v, du + dv - k);
  }
}

void solve() {
  for (int i = 0; i < 10005; i++)
    g[i].clear();

  int n;
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }

  dfs(1);
  up[0][0] = 0; // make building the jump table easier

  // build the jump table
  for (int i = 1; i < 15; i++)
    for (int j = 0; j <= n; j++)
      up[i][j] = up[i - 1][up[i - 1][j]],
      dist[i][j] = dist[i - 1][j] + dist[i - 1][up[i - 1][j]];

  while (true) {
    string s;
    cin >> s;
    if (s == "DONE")
      break;
    if (s == "DIST") {
      int u, v;
      cin >> u >> v;
      cout << distf(u, v) << endl;
    }
    if (s == "KTH") {
      int u, v, k;
      cin >> u >> v >> k;
      cout << kth(u, v, k) << endl;
    }
  }
}

int main() {
  init();
  int t;
  cin >> t;
  for (int i = 0; i < t; i++)
    solve();
  return 0;
}
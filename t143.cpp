#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef tuple<int, int, int> elem;

int n, m, k, c, x, y, l;
int own[100005], inv[100005], mindist[100005];
vector<pair<int, int>> adj[100005];
priority_queue<elem, vector<elem>, greater<elem>> pq;

void init() {
  fill(own, own + 100005, -1);
  fill(mindist, mindist + 100005, 0x3f3f3f3f3f3fLL);

  inv[0] = 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  init();

  cin >> n >> m >> k;
  for (int i = 1; i <= k; i++) {
    cin >> c;
    pq.push(elem{0, c, c});
    mindist[c] = 0, inv[c] = i;
  }
  for (int i = 0; i < m; i++) {
    cin >> x >> y >> l;
    adj[x].push_back({l, y});
    adj[y].push_back({l, x});
  }

  while (!pq.empty()) {
    int dist, node, owner;
    tie(dist, node, owner) = pq.top(), pq.pop();

    if (dist > mindist[node])
      continue;

    if (own[node] == -1) {
      // First time visited node
      own[node] = owner;
    } else if (own[node] != owner) {
      // Second time visited node, discovered node has multiple nearest nodes
      own[node] = 0;
    } else {
      // No need to process this node.
      continue;
    }

    for (auto h : adj[node]) {
      if (dist + h.first <= mindist[h.second]) {
        pq.push(elem{dist + h.first, h.second, own[node]});
        mindist[h.second] = min(mindist[h.second], dist + h.first);
      }
    }
  }

  for (int i = 1; i <= n; i++)
    cout << inv[own[i]] << " ";
}
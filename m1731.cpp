#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 100005;
const int bs = 350;
struct ll3 {
  ll a, b, c;
};

ll dpfact[maxn] = {};
ll dpfactinv[maxn] = {};
ll inv2;
ll ans[maxn];
ll3 q[maxn];

ll bm(ll b, ll p, ll m) {
  if (p == 0)
    return 1;
  if (p & 1)
    return b * bm(b, p - 1, m) % m;
  return bm(b * b % m, p / 2, m);
}

ll modinv(ll x) { return bm(x, mod - 2, mod); }

ll ncr(ll n, ll k) {
  return dpfact[n] * dpfactinv[n - k] % mod * dpfactinv[k] % mod;
}

void init() {
  dpfact[0] = 1;
  for (int i = 1; i <= 100000; i++)
    dpfact[i] = dpfact[i - 1] * i % mod;
  for (int i = 0; i <= 100000; i++)
    dpfactinv[i] = modinv(dpfact[i]);
  inv2 = dpfactinv[2];
}

int main() {
  init();
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> q[i].a >> q[i].b;
    q[i].c = i;
  }
  sort(q, q + N, [](const ll3 &a, const ll3 &b) {
    if (a.a / bs != b.a / bs)
      return a.a / bs < b.a / bs;
    else
      return a.b < b.b;
  });
  ll n = 0, k = 0, ans = 1;
  for (int i = 0; i < N; i++) {
    while (n < q[i].a) {
      ans = (ans * 2 - ncr(n, k) + mod) % mod;
      n++;
    }
    while (n > q[i].a) {
      ans = (ans + ncr(n - 1, k)) * inv2 % mod;
      n--;
    }
    while (k < q[i].b) {
      ans = (ans + ncr(n, k + 1)) % mod;
      k++;
    }
    while (k > q[i].b) {
      ans = (ans - ncr(n, k) + mod) % mod;
      k--;
    }
    ::ans[q[i].c] = ans;
  }
  for (int i = 0; i < N; i++)
    cout << ::ans[i] << endl;
  return 0;
}
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;
typedef long long LL;

int main() {
  tree<LL,                               // Key type
       null_type,                        // Mapped type
       less_equal<LL>,                   // Comparator
       rb_tree_tag,                      // Tree type
       tree_order_statistics_node_update // Node update type (order statistics)
       >
      T;
  int n, prev;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int t;
    cin >> t;
    if (!i) {
      T.insert(t);
      prev = t;
    } else {
      int m = T.order_of_key(prev) + 1;
      cout << m << endl;
      T.insert(t + m);
      prev = t + m;
    }
  }
  cout << T.order_of_key(prev) + 1 << endl;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegTree {
  SegTree *sl, *sr; // left & right child.
  int l, r;         // the interval of current node.
  ll sum;           // the sum of elements in this node.
  ll lazy;          // value to be added to each value in the range.

  // create the segment tree node
  SegTree(int *init, int l, int r) : l(l), r(r), lazy(0) {
    // leaf node, no need to build children nodes
    if (l == r) {
      sum = init[l];
      return;
    }

    int m = l + r >> 1;

    // create the two children nodes
    sl = new SegTree(init, l, m);
    sr = new SegTree(init, m + 1, r);

    // calculate the current node
    sum = sl->sum + sr->sum;
  }

  // query the sum of a[ql..qr]
  ll query(int ql, int qr) {
    // current node is exactly what is needed
    if (ql == l && qr == r)
      return sum + lazy * (r - l + 1);

    int m = l + r >> 1;
    int v = (qr - ql + 1) * lazy;

    if (qr <= m) // query range is in left node
      return v + sl->query(ql, qr);
    else if (ql > m) // query range is in right node
      return v + sr->query(ql, qr);
    else // query range crosses both nodes
      return v + sl->query(ql, m) + sr->query(m + 1, qr);
  }

  // helper function to get the sum of the current node
  ll get() { return lazy * (r - l + 1) + sum; }

  // set a[ql..qr] += v
  void update(int ql, int qr, int v) {
    // current node is exact match
    if (ql == l && qr == r) {
      lazy += v;
      return;
    }

    int m = l + r >> 1;

    // pushdown: push the lazy value to a level lower
    sl->lazy += lazy, sr->lazy += lazy;
    lazy = 0;

    if (qr <= m) // update range is in left node
      sl->update(ql, qr, v);
    else if (ql > m) // update range is in right node
      sr->update(ql, qr, v);
    else // update range crosses both nodes
      sl->update(ql, m, v), sr->update(m + 1, qr, v);

    // recalculate current node
    sum = sl->get() + sr->get();
  }
};

int arr[100005];

int main() {
  // write your solution here...
  int n, q;
  cin >> n >> q;
  SegTree *tree = new SegTree(arr, 1, n);
  for (int i = 0; i < q; i++) {
    int y, s, t, x;
    cin >> y >> s >> t;
    if (y == 0)
      cin >> x;
    if (y == 0) {
      tree->update(s, t, x);
    } else {
      cout << tree->query(s, t) << endl;
    }
  }
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegTree {
  SegTree *sl, *sr; // left & right child.
  int l, r;         // the interval of current node.
  ll sum;           // the sum of elements in this node.

  // create the segment tree node
  SegTree(int *init, int l, int r) : l(l), r(r) {
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
      return sum;

    int m = l + r >> 1;

    if (qr <= m) // query range is in left node
      return sl->query(ql, qr);
    else if (ql > m) // query range is in right node
      return sr->query(ql, qr);
    else // query range crosses both nodes
      return sl->query(ql, m) + sr->query(m + 1, qr);
  }

  // set a[k] += v
  void update(int k, int v) {
    // current node is exact match
    if (l == r && l == k) {
      sum = v;
      return;
    }

    int m = l + r >> 1;

    if (k <= m) // updated node is on the left
      sl->update(k, v);
    else // updated node is on the right
      sr->update(k, v);

    // recalculate current node
    sum = sl->sum + sr->sum;
  }
};

int main() {
  // write your solution here...
}
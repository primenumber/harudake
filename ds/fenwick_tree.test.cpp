#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include <iostream>
#include <vector>
#include "ds/fenwick_tree.hpp"

#define rep2(i,k,n) for(i64 i=(i64)(k);i<(i64)(n);i++)
#define rep(i,n) rep2(i,0,n)
#define all(x) begin(x),end(x)
#ifdef ENV_LOCAL
#define dump if (1) cerr
#else
#define dump if (0) cerr
#endif

using namespace std;
using namespace std::string_literals;

using i32 = int32_t;
using i64 = int64_t;
using f64 = double;
using f80 = long double;
using vi32 = vector<i32>;
using vi64 = vector<i64>;

using namespace harudake;

int main() {
  i64 n,q;
  cin>>n>>q;
  fenwick_tree bit(n);
  rep(i,n) {
    i64 a;
    cin>>a;
    bit.update(i, a);
  }
  rep(qcnt,q) {
    i64 t;
    cin>>t;
    if(t==0) {
      i64 p,x;
      cin>>p>>x;
      bit.update(p, x);
    } else {
      i64 l,r;
      cin>>l>>r;
      auto res = bit.query(r-1) - bit.query(l-1);
      cout<<res<<"\n";
    }
  }
  return 0;
}

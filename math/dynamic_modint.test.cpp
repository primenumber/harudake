#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include <iostream>
#include <vector>

#include "math/dynamic_modint.hpp"

#define rep2(i, k, n) for (i64 i = (i64)(k); i < (i64)(n); i++)
#define rep(i, n) rep2(i, 0, n)
#define all(x) begin(x), end(x)
#ifdef ENV_LOCAL
#define dump                                                                                                           \
  if (1)                                                                                                               \
  cerr
#else
#define dump                                                                                                           \
  if (0)                                                                                                               \
  cerr
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
using modint = harudake::dynamic_modint<uint64_t>;

i64 det(vector<vector<modint>> mat) {
  i64 n = size(mat);
  modint ans(1);
  rep(i, n) {
    i32 pivot = -1;
    rep2(j, i, n) {
      if (mat[j][i].get() != 0)
        pivot = j;
    }
    if (pivot < 0)
      return 0;
    if (i != pivot) {
      swap(mat[i], mat[pivot]);
      ans *= modint(998244353 - 1);
    }
    rep2(j, i + 1, n) {
      auto scale = mat[j][i] / mat[i][i];
      rep2(k, i, n) { mat[j][k] -= mat[i][k] * scale; }
    }
  }
  rep(i, n) ans *= mat[i][i];
  return ans.get();
}

int main() {
  i32 n;
  cin >> n;
  modint::mod = 998244353;
  vector mat(n, vector<modint>(n));
  rep(i, n) rep(j, n) {
    i32 x;
    cin >> x;
    mat[i][j] = modint(x);
  }
  cout << det(mat) << endl;
  return 0;
}

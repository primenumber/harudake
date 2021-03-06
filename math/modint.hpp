/*
 * harudake::modint
 *
 * Copyright (c) 2021 prime number
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 *
 */
namespace harudake {

template <typename base_t, base_t MOD>
class static_modint;

using modint_1000000007 = static_modint<uint64_t, 1'000'000'007>;
using modint_998244353 = static_modint<uint64_t, 998'244'353>;

template <typename base_t, base_t MOD>
static_modint<base_t, MOD> add(const static_modint<base_t, MOD> lhs, const static_modint<base_t, MOD> rhs) {
  base_t tmp = lhs.val + rhs.val;
  if (tmp >= MOD) tmp -= MOD;
  return static_modint<base_t, MOD>::make_raw(tmp);
}

template <typename base_t, base_t MOD>
static_modint<base_t, MOD> sub(const static_modint<base_t, MOD> lhs, const static_modint<base_t, MOD> rhs) {
  base_t tmp = lhs.val + MOD - rhs.val;
  if (tmp >= MOD) tmp -= MOD;
  return static_modint<base_t, MOD>::make_raw(tmp);
}

template <typename base_t, base_t MOD>
static_modint<base_t, MOD> mul(const static_modint<base_t, MOD> lhs, const static_modint<base_t, MOD> rhs) {
  base_t tmp = lhs.val * rhs.val;
  tmp %= MOD;
  return static_modint<base_t, MOD>::make_raw(tmp);
}

// data types must be signed integer
inline int64_t inv (const int64_t a, const int64_t p) {
  return (a == 1 ? 1 : (1 - p * inv(p%a, a)) / a + p);
};

template <typename base_t, base_t MOD>
static_modint<base_t, MOD> div(const static_modint<base_t, MOD> lhs, const static_modint<base_t, MOD> rhs) {
  base_t tmp = lhs.val * inv(rhs.val, MOD);
  tmp %= MOD;
  return static_modint<base_t, MOD>::make_raw(tmp);
}

template <typename base_t, base_t MOD>
static_modint<base_t, MOD> pow(const static_modint<base_t, MOD> base, const uint64_t index) {
  if (index == 0) return static_modint<base_t, MOD> { 1 };
  if (index % 2 == 1) {
    return pow(base, index - 1) * base;
  } else {
    auto half = pow(base, index / 2);
    return half * half;
  }
}

template <typename base_t, base_t MOD>
class static_modint {
  using modint = static_modint;
 public:
  static constexpr base_t mod = MOD;
  static_modint() : val(0) {}
  static_modint(const base_t x) : val(x % MOD) {}
  static_modint(const modint&) = default;
  modint& operator=(const modint&) = default;
  modint& operator=(const base_t x) {
    val = x % MOD;
    return *this;
  }
  modint operator-() const { return val == 0 ? 0 : MOD - val; }
  explicit operator base_t() const { return val; }
  base_t get() const { return val; }
  constexpr base_t get_mod() const { return mod; }
  static modint make_raw(const base_t raw) {
    modint res;
    res.val = raw;
    return res;
  }
 private:
  friend modint add<base_t, MOD>(const modint, const modint);
  friend modint sub<base_t, MOD>(const modint, const modint);
  friend modint mul<base_t, MOD>(const modint, const modint);
  friend modint div<base_t, MOD>(const modint, const modint);
  base_t val;
};

template <typename base_t, base_t MOD>
static_modint<base_t, MOD> operator+(const static_modint<base_t, MOD> lhs, const static_modint<base_t, MOD> rhs) {
  return add(lhs, rhs);
}
template <typename base_t, base_t MOD>
static_modint<base_t, MOD> operator-(const static_modint<base_t, MOD> lhs, const static_modint<base_t, MOD> rhs) {
  return sub(lhs, rhs);
}
template <typename base_t, base_t MOD>
static_modint<base_t, MOD> operator*(const static_modint<base_t, MOD> lhs, const static_modint<base_t, MOD> rhs) {
  return mul(lhs, rhs);
}
template <typename base_t, base_t MOD>
static_modint<base_t, MOD> operator/(const static_modint<base_t, MOD> lhs, const static_modint<base_t, MOD> rhs) {
  return div(lhs, rhs);
}
template <typename base_t, base_t MOD>
static_modint<base_t, MOD> operator^(const static_modint<base_t, MOD> lhs, const uint64_t rhs) {
  return pow(lhs, rhs);
}

template <typename base_t, base_t MOD>
static_modint<base_t, MOD>& operator+=(static_modint<base_t, MOD>& lhs, const static_modint<base_t, MOD> rhs) {
  return lhs = lhs + rhs;
}
template <typename base_t, base_t MOD>
static_modint<base_t, MOD>& operator-=(static_modint<base_t, MOD>& lhs, const static_modint<base_t, MOD> rhs) {
  return lhs = lhs - rhs;
}
template <typename base_t, base_t MOD>
static_modint<base_t, MOD>& operator*=(static_modint<base_t, MOD>& lhs, const static_modint<base_t, MOD> rhs) {
  return lhs = lhs * rhs;
}
template <typename base_t, base_t MOD>
static_modint<base_t, MOD>& operator/=(static_modint<base_t, MOD>& lhs, const static_modint<base_t, MOD> rhs) {
  return lhs = lhs / rhs;
}
template <typename base_t, base_t MOD>
static_modint<base_t, MOD>& operator^=(static_modint<base_t, MOD>& lhs, const uint64_t rhs) {
  return lhs = lhs ^ rhs;
}

} // namespace harudake

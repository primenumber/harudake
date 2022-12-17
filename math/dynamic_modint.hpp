/*
 * harudake::dynamic_modint
 *
 * Copyright (c) 2022 prime number
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 *
 */
namespace harudake {

template <typename base_t> class dynamic_modint;

template <typename base_t>
dynamic_modint<base_t> add(const dynamic_modint<base_t> lhs, const dynamic_modint<base_t> rhs) {
  base_t tmp = lhs.val + rhs.val;
  if (tmp >= dynamic_modint<base_t>::mod)
    tmp -= dynamic_modint<base_t>::mod;
  return dynamic_modint<base_t>::make_raw(tmp);
}

template <typename base_t>
dynamic_modint<base_t> sub(const dynamic_modint<base_t> lhs, const dynamic_modint<base_t> rhs) {
  base_t tmp = lhs.val + dynamic_modint<base_t>::mod - rhs.val;
  if (tmp >= dynamic_modint<base_t>::mod)
    tmp -= dynamic_modint<base_t>::mod;
  return dynamic_modint<base_t>::make_raw(tmp);
}

template <typename base_t>
dynamic_modint<base_t> mul(const dynamic_modint<base_t> lhs, const dynamic_modint<base_t> rhs) {
  base_t tmp = lhs.val * rhs.val;
  tmp %= dynamic_modint<base_t>::mod;
  return dynamic_modint<base_t>::make_raw(tmp);
}

// data types must be signed integer
inline int64_t inv(const int64_t a, const int64_t p) { return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p); };

template <typename base_t>
dynamic_modint<base_t> div(const dynamic_modint<base_t> lhs, const dynamic_modint<base_t> rhs) {
  base_t tmp = lhs.val * inv(rhs.val, dynamic_modint<base_t>::mod);
  tmp %= dynamic_modint<base_t>::mod;
  return dynamic_modint<base_t>::make_raw(tmp);
}

template <typename base_t> dynamic_modint<base_t> pow(const dynamic_modint<base_t> base, const uint64_t index) {
  if (index == 0)
    return dynamic_modint<base_t>{1};
  if (index % 2 == 1) {
    return pow(base, index - 1) * base;
  } else {
    auto half = pow(base, index / 2);
    return half * half;
  }
}

template <typename base_t> class dynamic_modint {
  using modint = dynamic_modint;

public:
  static base_t mod;
  dynamic_modint() : val(0) {}
  dynamic_modint(const base_t x) : val(x % dynamic_modint<base_t>::mod) {}
  dynamic_modint(const modint &) = default;
  modint &operator=(const modint &) = default;
  modint &operator=(const base_t x) {
    val = x % dynamic_modint<base_t>::mod;
    return *this;
  }
  modint operator-() const { return val == 0 ? 0 : dynamic_modint<base_t>::mod - val; }
  explicit operator base_t() const { return val; }
  base_t get() const { return val; }
  constexpr base_t get_mod() const { return mod; }
  static modint make_raw(const base_t raw) {
    modint res;
    res.val = raw;
    return res;
  }

private:
  friend modint add<base_t>(const modint, const modint);
  friend modint sub<base_t>(const modint, const modint);
  friend modint mul<base_t>(const modint, const modint);
  friend modint div<base_t>(const modint, const modint);
  base_t val;
};

template <typename base_t> base_t dynamic_modint<base_t>::mod;

template <typename base_t>
dynamic_modint<base_t> operator+(const dynamic_modint<base_t> lhs, const dynamic_modint<base_t> rhs) {
  return add(lhs, rhs);
}
template <typename base_t>
dynamic_modint<base_t> operator-(const dynamic_modint<base_t> lhs, const dynamic_modint<base_t> rhs) {
  return sub(lhs, rhs);
}
template <typename base_t>
dynamic_modint<base_t> operator*(const dynamic_modint<base_t> lhs, const dynamic_modint<base_t> rhs) {
  return mul(lhs, rhs);
}
template <typename base_t>
dynamic_modint<base_t> operator/(const dynamic_modint<base_t> lhs, const dynamic_modint<base_t> rhs) {
  return div(lhs, rhs);
}
template <typename base_t> dynamic_modint<base_t> operator^(const dynamic_modint<base_t> lhs, const uint64_t rhs) {
  return pow(lhs, rhs);
}

template <typename base_t>
dynamic_modint<base_t> &operator+=(dynamic_modint<base_t> &lhs, const dynamic_modint<base_t> rhs) {
  return lhs = lhs + rhs;
}
template <typename base_t>
dynamic_modint<base_t> &operator-=(dynamic_modint<base_t> &lhs, const dynamic_modint<base_t> rhs) {
  return lhs = lhs - rhs;
}
template <typename base_t>
dynamic_modint<base_t> &operator*=(dynamic_modint<base_t> &lhs, const dynamic_modint<base_t> rhs) {
  return lhs = lhs * rhs;
}
template <typename base_t>
dynamic_modint<base_t> &operator/=(dynamic_modint<base_t> &lhs, const dynamic_modint<base_t> rhs) {
  return lhs = lhs / rhs;
}
template <typename base_t> dynamic_modint<base_t> &operator^=(dynamic_modint<base_t> &lhs, const uint64_t rhs) {
  return lhs = lhs ^ rhs;
}

} // namespace harudake

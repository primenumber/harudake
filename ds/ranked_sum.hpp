/*
 * harudake::ranked_sum
 *
 * Copyright (c) 2023 prime number
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 *
 */
#ifndef HARUDAKE_DS_RANKED_SUM_HPP
#define HARUDAKE_DS_RANKED_SUM_HPP
namespace harudake {

// sum of bottom-(rank) element
// rank can be (inc/dec)remented in O(log(N))
template <typename T>
struct ranked_sum {
 public:
  // n: number of elements
  // rank: initial rank
  // time complexity: O(N)
  ranked_sum(size_t n, size_t rank)
      : data(n, 0), lo(), hi(), rank(rank), sum(0) {
    rep(i, rank) { lo.emplace(T(0), i); }
    rep2(i, rank, n) { hi.emplace(T(0), i); }
  }

 private:
  void move_to_lo() {
    using std::begin;
    if (hi.empty()) return;
    auto p = *begin(hi);
    sum += p.first;
    lo.insert(p);
    hi.erase(p);
  }
  void move_to_hi() {
    using std::rbegin;
    if (lo.empty()) return;
    auto p = *rbegin(lo);
    sum -= p.first;
    hi.insert(p);
    lo.erase(p);
  }

 public:
  // set value of idx-th element (0-indexed) to val
  // time complexity: O(log(N))
  void set_val(size_t idx, T val) {
    using std::size;
    auto old = std::make_pair(data[idx], idx);
    if (lo.count(old)) {
      lo.erase(old);
      sum -= data[idx];
    }
    if (hi.count(old)) hi.erase(old);
    data[idx] = val;
    auto cur = std::make_pair(data[idx], idx);
    hi.insert(cur);
    // at here, we can assume: size(lo) <= rank
    while (!hi.empty() && size(lo) < rank) {
      move_to_lo();
    }
  }
  // get value of idx-th element (0-indexed)
  // time complexity: O(1)
  T get_val(size_t idx) const { return data[idx]; }
  // get current rank
  // time complexity: O(1)
  size_t get_rank() const { return rank; }
  // increment rank
  // time complexity: O(log(N))
  void inc_rank() {
    ++rank;
    if (size(lo) < rank) move_to_lo();
  }
  // decrement rank
  // time complexity: O(log(N))
  void dec_rank() {
    --rank;
    if (size(lo) > rank) move_to_hi();
  }
  // get sum of bottom-(rank) elements
  // time complexity: O(1)
  T get_sum() const { return sum; }

 private:
  std::vector<T> data;
  std::set<std::pair<T, size_t>> lo, hi;
  size_t rank;
  T sum;
};

}  // namespace harudake

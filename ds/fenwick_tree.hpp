/*
 * harudake::fenwick_tree
 *
 * Copyright (c) 2021 prime number
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 *
 */
#ifndef HARUDAKE_DS_FENWICK_TREE_HPP
#define HARUDAKE_DS_FENWICK_TREE_HPP
namespace harudake {

// Auto extended container
template <typename T, typename Container = std::vector<T>>
class auto_vector {
 public:
  auto_vector() : data() {}
  auto_vector(size_t N, T val = T()) : data(N, val) {}
  T& operator[](size_t index) {
    if (index >= std::size(data)) expand_to(index);
    return data[index];
  }
  const T& at(size_t index) const {
    return data.at(index);
  }
 private:
  void expand_to(size_t index) {
    size_t new_size = 1;
    while (index >= new_size) new_size *= 2;
    data.resize(new_size);
  }
  Container data;
};

// Binary Indexed Tree / Fenwick Tree
//
// 0-indexed
// containers can be used:
// auto_vector, unrodered_map or map

template <typename T = int64_t, typename Container = auto_vector<T>, typename F = std::plus<T>>
class fenwick_tree {
 public:
  fenwick_tree(size_t N) : N(N), data() {}
  fenwick_tree(size_t N, F merge) : N(N), data(), merge(merge) {}
  void update(size_t index, const T& value) {
    for (; index < N; index |= index+1) {
      data[index] = merge(data[index], value);
    }
  }
  T query(ptrdiff_t index) {
    T result{};
    for (; index >= 0; index = (index&(index+1))-1) {
      result = merge(result, data[index]);
    }
    return result;
  }
 private:
  size_t N;
  Container data;
  F merge;
};

} // namespace harudake
#endif // HARUDAKE_DS_FENWICK_TREE_HPP

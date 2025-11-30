#ifndef POINT_HPP
#define POINT_HPP

#include <concepts>

template <class T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
struct Point {
  T x;
  T y;

  Point(): x(0), y(0) {}
  Point(T _x, T _y): x(_x), y(_y) {}
};

#endif

#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "./point.hpp"
#include <memory>

#define EPSILON         1e-6
#define COUNT_OF_POINTS    4

template <Scalar T>
double side(const std::unique_ptr<Point<T>> &p1, const std::unique_ptr<Point<T>> &p2) {
  const double sideX = static_cast<double>(p1->x - p2->x);
  const double sideY = static_cast<double>(p1->y - p2->y);
  return (std::sqrt(sideX * sideX + sideY * sideY));
}

template <Scalar T>
bool isGoodPoints(const std::unique_ptr<Point<T>> &p1, const std::unique_ptr<Point<T>> &p2, Point<T> normalDelta) {
  const Point<T> currentDelta(fabs(p1->x - p2->x), fabs(p1->y - p2->y));
  const bool xIsGood = fabs(currentDelta.x - normalDelta.x) < EPSILON;
  const bool yIsGood = fabs(currentDelta.y - normalDelta.y) < EPSILON;
  return xIsGood && yIsGood;
}

#endif

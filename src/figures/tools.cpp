#include "../../include/figures.hpp"
#include "../../include/point.hpp"
#include <cmath>

template <Scalar T>
double side(Point<T> p1, Point<T> p2) {
  const double sideX = static_cast<double>(p1.x - p2.x);
  const double sideY = static_cast<double>(p1.y - p2.y);
  return (sqrt(sideX * sideX + sideY * sideY));
}

#include "../../include/figures.hpp"
#include "../../include/point.hpp"
#include <cmath>

template <Scalar T>
double side(Point<T> p1, Point<T> p2) {
  const double sideX = static_cast<double>(p1.x - p2.x);
  const double sideY = static_cast<double>(p1.y - p2.y);
  return (sqrt(sideX * sideX + sideY * sideY));
}

template <Scalar T>
double Rhomb<T>::square() const {
  const double d1 = side(*points[0], *points[2]);
  const double d2 = side(*points[1], *points[3]);
  return d1 * d2 / 2.0;
}

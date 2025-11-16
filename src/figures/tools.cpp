#include "../../include/figures.hpp"
#include "../../include/point.hpp"
#include <cmath>

#define EPSILON 1e-6

template <Scalar T>
double side(Point<T> p1, Point<T> p2) {
  const double sideX = static_cast<double>(p1.x - p2.x);
  const double sideY = static_cast<double>(p1.y - p2.y);
  return (std::sqrt(sideX * sideX + sideY * sideY));
}

template <Scalar T>
Point<T> Figure<T>::center() const {
  Point<T> p;
  p.x = (points[0]->x + points[1]->x + points[2]->x + points[3]->x) / 4.0;
  p.y = (points[0]->y + points[1]->y + points[2]->y + points[3]->y) / 4.0;
  return p;
}

template <Scalar T>
double Rectangle<T>::square() const {
  const double side1 = side(*points[0], *points[1]);
  const double side2 = side(*points[1], *points[2]);
  return side1 * side2;
}

/*    a
   0_____1
   /     \
c /       \ d
 /         \
3‾‾‾‾‾‾‾‾‾‾‾2
      b        */
template <Scalar T>
double Trapezoid<T>::square() const {  
  const double base1Tmp = side(*points[0], *points[1]);
  const double side1Tmp = side(*points[1], *points[2]);
  const double base2Tmp = side(*points[2], *points[3]);
  const double side2Tmp = side(*points[3], *points[0]);
  
  const double a = std::min(base1Tmp, base2Tmp);
  const double b = std::max(base1Tmp, base2Tmp);
  const double c = (base1Tmp < base2Tmp) ? side2Tmp : side1Tmp;
  const double d = (base1Tmp < base2Tmp) ? side1Tmp : side2Tmp;

  if (std::fabs(a - b) < EPSILON) {
    throw IncorrectFigureException();
  }

  const double fracBeforeSqrt = (a + b) / 2.0;
  const double fracUnderSqrt = ((a - b) * (a - b) + c * c - d * d) / (2.0 * (a - b));
  
  const double _square = fracBeforeSqrt * std::sqrt(c * c - fracUnderSqrt * fracUnderSqrt);
  if (_square < 0) {
    throw IncorrectFigureException();
  }
  return _square;
}

template <Scalar T>
double Rhomb<T>::square() const {
  const double d1 = side(*points[0], *points[2]);
  const double d2 = side(*points[1], *points[3]);
  return d1 * d2 / 2.0;
}

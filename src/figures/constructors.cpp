#include "../../include/figures.hpp"
#include "../../include/point.hpp"
#include <vector>
#include <memory>

#define COUNT_OF_POINTS 4

template <Scalar T>
Figure<T>::Figure() {
  for (size_t i = 0; i != COUNT_OF_POINTS; ++i) {
    points.push_back(std::make_unique<Point<T>>(0, 0));
  }
}

template <Scalar T>
Figure<T>::Figure(const std::vector<Point<T>> &_points) {
  if (_points.size() != static_cast<size_t>(COUNT_OF_POINTS)) {
    throw IncorrectPointsCountException();
  }
  for (size_t i = 0; i != COUNT_OF_POINTS; ++i) {
    points.push_back(std::make_unique<Point<T>>(_points[i]));
  }
}

template <Scalar T>
Rectangle<T>::Rectangle(): Figure<T>() {}

template <Scalar T>
Rectangle<T>::Rectangle(const std::vector<Point<T>> &_points): Figure<T>(_points) {}

template <Scalar T>
Trapezoid<T>::Trapezoid(): Figure<T>() {}

template <Scalar T>
Trapezoid<T>::Trapezoid(const std::vector<Point<T>> &_points): Figure<T>(_points) {}

template <Scalar T>
Rhomb<T>::Rhomb(): Figure<T>() {}

template <Scalar T>
Rhomb<T>::Rhomb(const std::vector<Point<T>> &_points): Figure<T>(_points) {}

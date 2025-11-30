#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <cmath>
#include "./point.hpp"
#include "./tools.hpp"

template <Scalar T>
class Figure {
  protected:
    std::vector<std::unique_ptr<Point<T>>> points;

    Figure() {
      for (size_t i = 0; i != COUNT_OF_POINTS; ++i) {
        points.push_back(std::make_unique<Point<T>>(0, 0));
      } 
    }
    Figure(const std::vector<Point<T>> &_points) {
      if (_points.size() != static_cast<size_t>(COUNT_OF_POINTS)) {
        throw IncorrectPointsCountException();
      }
      for (size_t i = 0; i != COUNT_OF_POINTS; ++i) {
        points.push_back(std::make_unique<Point<T>>(_points[i]));
      }
    }
  
  public:
    virtual ~Figure() = default;

    virtual double square() const = 0;
    Point<T> center() const {
      Point<T> p;
      p.x = (this->points[0]->x + this->points[1]->x + this->points[2]->x + this->points[3]->x) / 4.0;
      p.y = (this->points[0]->y + this->points[1]->y + this->points[2]->y + this->points[3]->y) / 4.0;
      return p;
    }

    Figure<T> &operator=(const Figure<T> &other) {
      if (this != &other) {
        points = other.points;
      }
      return *this;
    }

    Figure<T> &operator=(Figure<T> &&other) noexcept {
      if (this != &other) {
        points = std::move(other.points);
        other.points.clear();
      }
      return *this;
    }

    friend std::istream &operator>>(std::istream &in, Figure<T> &f) {
      if (f.points.size() != COUNT_OF_POINTS) {
        throw Figure<T>::EmptyFigureException();
      }

      for (size_t i = 0; i != COUNT_OF_POINTS; ++i) {
        std::cin >> f.points[i]->x >> f.points[i]->y;
      }

      return in;
    }
    
    friend std::ostream &operator<<(std::ostream &out, const Figure<T> &f) {
      if (f.points.size() != COUNT_OF_POINTS) {
        throw Figure<T>::EmptyFigureException();
      }

      for (size_t i = 0; i != COUNT_OF_POINTS; ++i) {
        if (i > 0) {
          std::cout << " ";
        }
        std::cout << "(" << f.points[i]->x << ", " << f.points[i]->y << ")";
      }

      return out;
    }
    
    friend bool operator==(const Figure<T> &l, const Figure<T> &r) {
      if (l.points.size() != COUNT_OF_POINTS || r.points.size() != COUNT_OF_POINTS) {
        throw Figure<T>::EmptyFigureException();
      }

      const Point<T> normalDelta(
        fabs(l.points[0]->x - r.points[0]->x),
        fabs(l.points[0]->y - r.points[0]->y)
      );
      
      for (size_t i = 1; i != COUNT_OF_POINTS; ++i) {
        if (!isGoodPoints(l.points[i], r.points[i], normalDelta)) {
          return false;
        }
      }
      return true;
    }

    class EmptyFigureException {};
    class IncorrectPointsCountException {};
    class IncorrectFigureException {};
};

template <Scalar T>
class Rectangle: public Figure<T> {
  public:
    Rectangle(): Figure<T>() {}
    Rectangle(const std::vector<Point<T>> &_points): Figure<T>(_points) {}

    double square() const override {
      const double side1 = side(this->points[0], this->points[1]);
      const double side2 = side(this->points[1], this->points[2]);
      const double _square = side1 * side2;
      if (_square < EPSILON) {
        throw typename Figure<T>::IncorrectFigureException();
      }
      return _square;
    }
};

template <Scalar T>
class Trapezoid: public Figure<T> {
  public:
    Trapezoid(): Figure<T>() {}
    Trapezoid(const std::vector<Point<T>> &_points): Figure<T>(_points) {}

    /*    a
       0_____1
       /     \
    c /       \ d
     /         \
    3‾‾‾‾‾‾‾‾‾‾‾2
          b        */
    double square() const override {
      const double base1Tmp = side(this->points[0], this->points[1]);
      const double side1Tmp = side(this->points[1], this->points[2]);
      const double base2Tmp = side(this->points[2], this->points[3]);
      const double side2Tmp = side(this->points[3], this->points[0]);
      
      const double a = std::min(base1Tmp, base2Tmp);
      const double b = std::max(base1Tmp, base2Tmp);
      const double c = (base1Tmp < base2Tmp) ? side2Tmp : side1Tmp;
      const double d = (base1Tmp < base2Tmp) ? side1Tmp : side2Tmp;

      if (std::fabs(a - b) < EPSILON) {
        throw typename Figure<T>::IncorrectFigureException();
      }

      const double fracBeforeSqrt = (a + b) / 2.0;
      const double fracUnderSqrt = ((a - b) * (a - b) + c * c - d * d) / (2.0 * (a - b));
      const double valueUnderSqrt = c * c - fracUnderSqrt * fracUnderSqrt;
      if (valueUnderSqrt < 0) {
        throw typename Figure<T>::IncorrectFigureException();
      }
      const double _square = fracBeforeSqrt * std::sqrt(valueUnderSqrt);
      if (_square < EPSILON) {
        throw typename Figure<T>::IncorrectFigureException();
      }
      return _square;
    }
};

template <Scalar T>
class Rhomb: public Figure<T> {
  public:
    Rhomb(): Figure<T>() {}
    Rhomb(const std::vector<Point<T>> &_points): Figure<T>(_points) {}

    double square() const override {
      const double d1 = side(this->points[0], this->points[2]);
      const double d2 = side(this->points[1], this->points[3]);
      const double _square = d1 * d2 / 2.0;
      if (_square < EPSILON) {
        throw typename Figure<T>::IncorrectFigureException();
      }
      return _square;
    }
};

#endif

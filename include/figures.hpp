#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <vector>
#include <memory>
#include <iostream>
#include "./point.hpp"

template <Scalar T>
class Figure {
  protected:
    std::vector<std::unique_ptr<Point<T>>> points;

    Figure();
    Figure(const std::vector<Point<T>> &_points);
  
  public:
    virtual ~Figure() = default;

    virtual double square() const = 0;
    Point<T> center() const;

    Figure<T> &operator=(const Figure<T> &other);
    Figure<T> &operator=(Figure<T> &&other) noexcept;

    friend std::ostream &operator<<<>(std::ostream &out, const Figure<T> &f);
    friend std::istream &operator>><>(std::istream &in, Figure<T> &f);
    friend bool operator==<>(const Figure<T> &l, const Figure<T> &r);

    class EmptyFigureException {};
    class IncorrectPointsCountException {};
    class IncorrectFigureException {};
};

template <Scalar T>
class Rectangle: public Figure<T> {
  public:
    Rectangle();
    Rectangle(const std::vector<Point<T>> &ps);

    double square() const override;
};

template <Scalar T>
class Trapezoid: public Figure<T> {
  public:
    Trapezoid();
    Trapezoid(const std::vector<Point<T>> &ps);

    double square() const override;
};

template <Scalar T>
class Rhomb: public Figure<T> {
  public:
    Rhomb();
    Rhomb(const std::vector<Point<T>> &ps);

    double square() const override;
};

#endif

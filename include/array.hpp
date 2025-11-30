#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "./figures.hpp"
#include "./point.hpp"
#include <vector>
#include <memory>

template <Scalar T>
class FiguresArray {
  private:
    std::vector<std::shared_ptr<Figure<T>>> figures;
  
  public:
    FiguresArray() = default;

    FiguresArray(size_t n, std::shared_ptr<Figure<T>> _figure = nullptr) {
      for (size_t i = 0; i != n; ++i) {
        figures.push_back(_figure);
      }
    }

    FiguresArray(const std::initializer_list<std::shared_ptr<Figure<T>>> &_figures) {
      figures = _figures;
    }

    FiguresArray(const std::vector<std::shared_ptr<Figure<T>>> &_figures) {
      figures = _figures;
    }

    FiguresArray(const FiguresArray &other) {
      for (size_t i = 0; i != other.figures.size(); ++i) {
        figures.push_back(other.figures[i]);
      }
    }

    FiguresArray(FiguresArray &&other) noexcept {
      figures = other.figures;
    }

    void printCenters() const {
      struct Point<T> c;
      for (size_t i = 0; i != figures.size(); ++i) {
        c = figures[i]->center();
        if (i > 0) {
          std::cout << " ";
        }
        std::cout << "(" << c.x << ", " << c.y << ")";
      }
    }

    void printSquares() const {
      for (size_t i = 0; i != figures.size(); ++i) {
        if (i > 0) {
          std::cout << " ";
        }
        std::cout << figures[i]->square();
      }
    }

    double sumOfSquares() const {
      double sum = 0;
      for (size_t i = 0; i != figures.size(); ++i) {
        sum += figures[i]->square();
      }
      return sum;
    }

    size_t getSize() const {
      return figures.size();
    }

    void pushBack(std::shared_ptr<Figure<T>> _figure) {
      figures.push_back(_figure);
    }

    void remove(const size_t i) {
      if (i >= figures.size()) {
        throw InvalidIndexException();
      }
      figures.erase(figures.begin() + i);
    }

    class InvalidIndexException {};
};

#endif

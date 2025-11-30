#include <gtest/gtest.h>
#include "./include/array.hpp"
#include "./include/figures.hpp"
#include "./include/point.hpp"
#include <memory>
#include <vector>

// Тесты для класса Point
TEST(PointTest, Constructor) {
  Point<double> p(1.0, 2.0);
  EXPECT_DOUBLE_EQ(p.x, 1.0);
  EXPECT_DOUBLE_EQ(p.y, 2.0);
}

TEST(PointTest, DefaultConstructor) {
  Point<double> p;
  EXPECT_DOUBLE_EQ(p.x, 0.0);
  EXPECT_DOUBLE_EQ(p.y, 0.0);
}

// Тесты для класса Rectangle
TEST(RectangleTest, DefaultConstructor) {
  Rectangle<double> rect;
  EXPECT_NO_THROW(rect.center());
}

TEST(RectangleTest, ConstructorWithPoints) {
  std::vector<Point<double>> points = {
    Point<double>(0, 0),
    Point<double>(4, 0),
    Point<double>(4, 3),
    Point<double>(0, 3)
  };
  
  Rectangle<double> rect(points);
  Point<double> center = rect.center();
  EXPECT_NEAR(center.x, 2.0, 1e-6);
  EXPECT_NEAR(center.y, 1.5, 1e-6);
}

TEST(RectangleTest, SquareCalculation) {
  std::vector<Point<double>> points = {
    Point<double>(0, 0),
    Point<double>(4, 0),
    Point<double>(4, 3),
    Point<double>(0, 3)
  };
    
  Rectangle<double> rect(points);
  double square = rect.square();
  EXPECT_NEAR(square, 12.0, 1e-6);
}

TEST(RectangleTest, InvalidRectangle) {
  std::vector<Point<double>> points = {
    Point<double>(0, 0),
    Point<double>(0, 0),
    Point<double>(0, 0),
    Point<double>(0, 0)
  };
  
  Rectangle<double> rect(points);
  EXPECT_THROW(rect.square(), Figure<double>::IncorrectFigureException);
}

// Тесты для класса Rhomb
TEST(RhombTest, ConstructorWithPoints) {
  std::vector<Point<double>> points = {
    Point<double>(0, 2),
    Point<double>(2, 0),
    Point<double>(0, -2),
    Point<double>(-2, 0)
  };
  
  Rhomb<double> rhomb(points);
  Point<double> center = rhomb.center();
  EXPECT_NEAR(center.x, 0.0, 1e-6);
  EXPECT_NEAR(center.y, 0.0, 1e-6);
}

TEST(RhombTest, SquareCalculation) {
  std::vector<Point<double>> points = {
    Point<double>(0, 2),
    Point<double>(2, 0),
    Point<double>(0, -2),
    Point<double>(-2, 0)
  };
  
  Rhomb<double> rhomb(points);
  double square = rhomb.square();
  EXPECT_NEAR(square, 8.0, 1e-6); // Площадь = (диагональ1 * диагональ2) / 2 = (4 * 4) / 2 = 8
}

// Тесты для класса Trapezoid
TEST(TrapezoidTest, ConstructorWithPoints) {
  std::vector<Point<double>> points = {
    Point<double>(1, 0),
    Point<double>(3, 0),
    Point<double>(4, 3),
    Point<double>(0, 3)
  };
  
  Trapezoid<double> trapezoid(points);
  Point<double> center = trapezoid.center();
  EXPECT_NEAR(center.x, 2.0, 1e-6);
  EXPECT_NEAR(center.y, 1.5, 1e-6);
}

// Тесты для класса FiguresArray
TEST(FiguresArrayTest, DefaultConstructor) {
  FiguresArray<double> array;
  EXPECT_EQ(array.getSize(), 0);
}

TEST(FiguresArrayTest, ConstructorWithSize) {
  FiguresArray<double> array(3);
  EXPECT_EQ(array.getSize(), 3);
}

TEST(FiguresArrayTest, PushBack) {
  FiguresArray<double> array;
  auto rect = std::make_shared<Rectangle<double>>();
  array.pushBack(rect);
  EXPECT_EQ(array.getSize(), 1);
}

TEST(FiguresArrayTest, Remove) {
  FiguresArray<double> array;
  auto rect1 = std::make_shared<Rectangle<double>>();
  auto rect2 = std::make_shared<Rectangle<double>>();
  
  array.pushBack(rect1);
  array.pushBack(rect2);
  
  EXPECT_EQ(array.getSize(), 2);
  array.remove(0);
  EXPECT_EQ(array.getSize(), 1);
}

TEST(FiguresArrayTest, RemoveInvalidIndex) {
  FiguresArray<double> array;
  auto rect = std::make_shared<Rectangle<double>>();
  array.pushBack(rect);
  
  EXPECT_THROW(array.remove(5), FiguresArray<double>::InvalidIndexException);
}

TEST(FiguresArrayTest, SumOfSquares) {
  std::vector<Point<double>> rect_points = {
    Point<double>(0, 0),
    Point<double>(4, 0),
    Point<double>(4, 3),
    Point<double>(0, 3)
  };
  
  auto rect = std::make_shared<Rectangle<double>>(rect_points);
  
  FiguresArray<double> array;
  array.pushBack(rect);
  
  double sum = array.sumOfSquares();
  EXPECT_NEAR(sum, 12.0, 1e-6);
}

TEST(FiguresArrayTest, CopyConstructor) {
  FiguresArray<double> array1;
  auto rect = std::make_shared<Rectangle<double>>();
  array1.pushBack(rect);
  
  FiguresArray<double> array2(array1);
  EXPECT_EQ(array2.getSize(), 1);
}

TEST(FiguresArrayTest, MoveConstructor) {
  FiguresArray<double> array1;
  auto rect = std::make_shared<Rectangle<double>>();
  array1.pushBack(rect);
  
  FiguresArray<double> array2(std::move(array1));
  EXPECT_EQ(array2.getSize(), 1);
}

// Тесты для операторов сравнения
TEST(FigureTest, EqualityOperator) {
  std::vector<Point<double>> points1 = {
    Point<double>(0, 0),
    Point<double>(4, 0),
    Point<double>(4, 3),
    Point<double>(0, 3)
  };
    
  std::vector<Point<double>> points2 = {
    Point<double>(0, 0),
    Point<double>(4, 0),
    Point<double>(4, 3),
    Point<double>(0, 3)
  };
  
  Rectangle<double> rect1(points1);
  Rectangle<double> rect2(points2);
  
  EXPECT_TRUE(rect1 == rect2);
}

// Тесты для исключений
TEST(FigureTest, IncorrectPointsCountException) {
  std::vector<Point<double>> points = {
    Point<double>(0, 0),
    Point<double>(1, 1)
  };
  
  EXPECT_THROW(Rectangle<double> rect(points), Figure<double>::IncorrectPointsCountException);
}

// Main function for Google Test
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

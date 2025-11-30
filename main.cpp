#include "./include/figures.hpp"
#include "./include/array.hpp"
#include <vector>
#include <memory>
#include <iostream>



int main() {
  std::shared_ptr rh1 = std::make_shared<Rhomb<double>>();
  std::shared_ptr r1 = std::make_shared<Rectangle<double>>();
  std::shared_ptr t1 = std::make_shared<Trapezoid<double>>();
  
  std::cin >> *rh1;
  std::cout << "rh1: " << *rh1 << std::endl;  // 0 2  3 0  0 -2  -3 0

  std::cin >> *r1;
  std::cout << "r1: " << *r1 << std::endl;    // 0 0  4 0  4 3  0 3

  std::cin >> *t1;
  std::cout << "t1: " << *t1 << std::endl;    // 2 0  4 0  0 3  6 3

  FiguresArray<double> arr1;
  arr1.pushBack(rh1);
  arr1.pushBack(r1);
  arr1.pushBack(t1);

  std::cout << "arr1.getSize(): " << arr1.getSize() << std::endl;
  
  std::cout << "arr1.printCenters(): ";
  arr1.printCenters();
  std::cout << std::endl;
  
  std::cout << "arr1.printSquares(): ";
  arr1.printSquares();
  std::cout << std::endl;

  std::cout << "arr1.sumOfSquares(): " << arr1.sumOfSquares() << std::endl;

  arr1.remove(2);
  std::cout << "arr1.printCenters(): ";
  arr1.printCenters();
  std::cout << std::endl;

  return 0;
}

#include <iostream>

// Base class
class Car {
  public:
    void printWheels() {
      std::cout << "A car has 4 wheels \n";
    }
    void printMake() {
      std::cout << "Make of Car \n";
    }
};

// Derived class
class Crosstrek : public Car {
  public:
    void printMake() {
      std::cout << "Subaru \n";
    }
};

// Derived class
class Tacoma : public Car {
  public:
    void printMake() {
      std::cout << "Toyota \n";
    }
};

int main() {
  Car car;
  Crosstrek crosstrek;
  Tacoma tacoma;

  car.printWheels();
  crosstrek.printWheels();
  tacoma.printWheels();
  car.printMake();
  crosstrek.printMake();
  tacoma.printMake();
  return 0;
}
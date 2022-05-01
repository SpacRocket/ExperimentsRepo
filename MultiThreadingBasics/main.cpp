
#include <iostream>
#include <thread>

int main() {
  int result = 0;
  std::thread tB = std::thread([&]() {
    std::cout << "Thread";
    result = 42;
  });
  tB.join();
  std::cout << result;
}
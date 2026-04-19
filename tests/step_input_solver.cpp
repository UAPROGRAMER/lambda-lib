#include <lambdalib/lambdalib.hpp>

#include <iostream>

using namespace std;
using namespace llib;
using namespace llib::def;

int main() {
  std::string source;

  std::getline(cin, source);

  unique_ptr<LambdaBase> expression;

  try {
    expression = parse(source);
  } catch (const std::runtime_error& e) {
    std::cout << "Bad expression: " << e.what() << '\n';
    return 1;
  }

  while (reduceOnce(expression)) {
    print(expression);
    std::cout << '\n';
  }

  return 0;
}
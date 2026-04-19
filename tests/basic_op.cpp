#include <lambdalib/lambdalib.hpp>

#include <iostream>

using namespace std;
using namespace llib;
using namespace llib::def;

int main() {
  unique_ptr<LambdaBase> expression =  //
    make_unique<Application>(          //
      make_unique<Application>(        //
        AND(),                         //
        FALSE()                        //
        ),                             //
      TRUE()                           //
    );                                 //

  print(expression);
  std::cout << '\n';

  reduce(expression);

  print(expression);
  std::cout << '\n';

  return 0;
}
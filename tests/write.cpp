#include <lambdalib/lambdalib.hpp>

#include <iostream>

using namespace std;
using namespace llib;
using namespace llib::def;

int main() {
  unique_ptr<LambdaBase> expression =  //
    make_unique<Application>(          //
      make_unique<Application>(        //
        make_unique<Application>(      //
          IFTHENELSE(),                //
          TRUE()                       //
          ),                           //
        TRUE()                         //
        ),                             //
      TRUE()                           //
    );                                 //

  ReduceVisitor reduceVisitor;

  PrintVisitor printVisitor;

  printVisitor.accept(expression);
  std::cout << '\n';

  reduceVisitor.accept(expression);

  printVisitor.accept(expression);
  std::cout << '\n';

  return 0;
}
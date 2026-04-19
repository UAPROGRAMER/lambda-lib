#pragma once

#include <iostream>

#include "nodes.hpp"

namespace llib {

class PrintVisitor {
private:
  bool outlineFunction = false;

  void accept(std::unique_ptr<Variable>& node) { std::cout << node->name; }

  void accept(std::unique_ptr<Function>& node) {
    if (outlineFunction) std::cout << '(';
    std::cout << '&' << node->argument.name << '.';
    accept(node->body);
    if (outlineFunction) std::cout << ')';
  }

  void accept(std::unique_ptr<Application>& node) {
    std::cout << '(';
    accept(node->left);
    accept(node->right);
    std::cout << ')';
  }

public:
  PrintVisitor() = default;
  PrintVisitor(bool outlineFunction) : outlineFunction(outlineFunction) {}

  void accept(std::unique_ptr<LambdaBase>& node) {
    switch (node->getType()) {
      case LambdaType::VARIABLE:
        return accept((std::unique_ptr<Variable>&)(node));
      case LambdaType::FUNCTION:
        return accept((std::unique_ptr<Function>&)(node));
      case LambdaType::APPLICATION:
        return accept((std::unique_ptr<Application>&)(node));
    }
  }
};

inline void print(std::unique_ptr<LambdaBase>& node) {
  return PrintVisitor().accept(node);
}

}  // namespace lambdalib
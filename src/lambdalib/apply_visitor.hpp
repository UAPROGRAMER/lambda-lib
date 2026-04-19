#pragma once

#include "nodes.hpp"

namespace llib {

class ApplyVisitor {
private:
  Variable argument;
  std::unique_ptr<LambdaBase> value;

  void accept(std::unique_ptr<Variable>& node) {
    if (argument == *node) (std::unique_ptr<LambdaBase>&)node = value->copy();
  }

  void accept(std::unique_ptr<Function>& node) {
    if (argument == node->argument) return;

    accept(node->body);
  }

  void accept(std::unique_ptr<Application>& node) {
    accept(node->left);
    accept(node->right);
  }

public:
  ApplyVisitor() = delete;
  ApplyVisitor(Variable argument, std::unique_ptr<LambdaBase> value)
    : argument(argument), value(std::move(value)) {}

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

}  // namespace llib
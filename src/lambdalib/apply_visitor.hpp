#pragma once

#include "nodes.hpp"

namespace llib {

class ApplyVisitor {
private:
  Variable input;
  std::unique_ptr<LambdaBase> value;

  void accept(std::unique_ptr<Variable>& node) {
    if (input == *node) (std::unique_ptr<LambdaBase>&)node = value->copy();
  }

  void accept(std::unique_ptr<Function>& node) {
    if (input == node->input) return;

    accept(node->body);
  }

  void accept(std::unique_ptr<Application>& node) {
    accept(node->func);
    accept(node->input);
  }

public:
  ApplyVisitor() = delete;
  ApplyVisitor(Variable input, std::unique_ptr<LambdaBase> value)
    : input(input), value(std::move(value)) {}

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
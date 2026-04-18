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

class ReduceVisitor {
private:
  void acceptVar(std::unique_ptr<LambdaBase>& node) {}

  void acceptFunc(std::unique_ptr<LambdaBase>& node) {
    accept(((std::unique_ptr<Function>&)node)->body);
  }

  bool acceptApp(std::unique_ptr<LambdaBase>& node) {
    std::unique_ptr<Application>& app = (std::unique_ptr<Application>&)node;

    if (app->func->getType() != LambdaType::FUNCTION)
      accept(app->func);

    if (app->func->getType() == LambdaType::FUNCTION) {
      std::unique_ptr<Function>& function =
        (std::unique_ptr<Function>&)app->func;
      
      ApplyVisitor applyVisitor(function->input, std::move(app->input));

      node = std::move(function->body);

      applyVisitor.accept(node);

      return true;
    }

    accept(app->input);

    return false;
  }

public:
  void accept(std::unique_ptr<LambdaBase>& node) {
    switch (node->getType()) {
      case LambdaType::VARIABLE:
        return acceptVar(node);
      case LambdaType::FUNCTION:
        return acceptFunc(node);
      case LambdaType::APPLICATION:
        if (acceptApp(node)) return accept(node);
    }
  }
};

}  // namespace lambdalib
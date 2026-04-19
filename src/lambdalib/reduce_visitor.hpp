#pragma once

#include "nodes.hpp"
#include "apply_visitor.hpp"

namespace llib {

// There is a good way to combine these 2 classes, but it isn't worth it for now
// (probably shouldn't use classes at all)

class ReduceVisitor {
private:
  void acceptVar(std::unique_ptr<LambdaBase>& node) {}

  void acceptFunc(std::unique_ptr<LambdaBase>& node) {
    accept(((std::unique_ptr<Function>&)node)->body);
  }

  bool acceptApp(std::unique_ptr<LambdaBase>& node) {
    std::unique_ptr<Application>& app = (std::unique_ptr<Application>&)node;

    if (app->left->getType() != LambdaType::FUNCTION) accept(app->left);

    if (app->left->getType() == LambdaType::FUNCTION) {
      std::unique_ptr<Function>& function =
        (std::unique_ptr<Function>&)app->left;

      ApplyVisitor applyVisitor(function->argument, std::move(app->right));

      node = std::move(function->body);

      applyVisitor.accept(node);

      return true;
    }

    accept(app->right);

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

class ReduceOnceVisitor {
private:
  bool acceptVar(std::unique_ptr<LambdaBase>& node) { return false; }

  bool acceptFunc(std::unique_ptr<LambdaBase>& node) {
    return accept(((std::unique_ptr<Function>&)node)->body);
  }

  bool acceptApp(std::unique_ptr<LambdaBase>& node) {
    std::unique_ptr<Application>& app = (std::unique_ptr<Application>&)node;

    if (app->left->getType() != LambdaType::FUNCTION) {
      accept(app->left);
      return true;
    }

    if (app->left->getType() == LambdaType::FUNCTION) {
      std::unique_ptr<Function>& function =
        (std::unique_ptr<Function>&)app->left;

      ApplyVisitor applyVisitor(function->argument, std::move(app->right));

      node = std::move(function->body);

      applyVisitor.accept(node);

      return true;
    }

    accept(app->right);

    return false;
  }

public:
  bool accept(std::unique_ptr<LambdaBase>& node) {
    switch (node->getType()) {
      case LambdaType::VARIABLE:
        return acceptVar(node);
      case LambdaType::FUNCTION:
        return acceptFunc(node);
      case LambdaType::APPLICATION:
        return acceptApp(node);
    }

    return false;
  }
};

inline void reduce(std::unique_ptr<LambdaBase>& node) {
  return ReduceVisitor().accept(node);
}

inline bool reduceOnce(std::unique_ptr<LambdaBase>& node) {
  return ReduceOnceVisitor().accept(node);
}

}  // namespace llib
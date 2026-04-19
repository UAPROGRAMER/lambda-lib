#pragma once

#include <memory>

namespace llib {

enum class LambdaType { VARIABLE, FUNCTION, APPLICATION };

class LambdaBase {
public:
  virtual ~LambdaBase() = default;

  virtual LambdaType getType() const = 0;

  virtual std::unique_ptr<LambdaBase> copy() const = 0;
};

class Variable : public LambdaBase {
public:
  char name;

  Variable(char name) : name(name) {}

  LambdaType getType() const override { return LambdaType::VARIABLE; }

  std::unique_ptr<LambdaBase> copy() const override {
    return std::make_unique<Variable>(name);
  }

  inline bool operator==(const Variable& other) const {
    return name == other.name;
  }
};

class Function : public LambdaBase {
public:
  Variable argument;
  std::unique_ptr<LambdaBase> body;

  Function(Variable argument, std::unique_ptr<LambdaBase> body)
    : argument(std::move(argument)), body(std::move(body)) {}

  LambdaType getType() const override { return LambdaType::FUNCTION; }

  std::unique_ptr<LambdaBase> copy() const override {
    return std::make_unique<Function>(argument, body->copy());
  }
};

class Application : public LambdaBase {
public:
  std::unique_ptr<LambdaBase> left;
  std::unique_ptr<LambdaBase> right;

  Application(
    std::unique_ptr<LambdaBase> left, std::unique_ptr<LambdaBase> right)
    : left(std::move(left)), right(std::move(right)) {}

  LambdaType getType() const override { return LambdaType::APPLICATION; }

  std::unique_ptr<LambdaBase> copy() const override {
    return std::make_unique<Application>(left->copy(), right->copy());
  }
};

}  // namespace llib
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
  char value;

  Variable(char value) : value(value) {}

  LambdaType getType() const override { return LambdaType::VARIABLE; }

  std::unique_ptr<LambdaBase> copy() const override {
    return std::make_unique<Variable>(value);
  }

  inline bool operator==(const Variable& other) const {
    return value == other.value;
  }
};

class Function : public LambdaBase {
public:
  Variable input;
  std::unique_ptr<LambdaBase> body;

  Function(Variable input, std::unique_ptr<LambdaBase> body)
    : input(std::move(input)), body(std::move(body)) {}

  LambdaType getType() const override { return LambdaType::FUNCTION; }

  std::unique_ptr<LambdaBase> copy() const override {
    return std::make_unique<Function>(input, body->copy());
  }
};

class Application : public LambdaBase {
public:
  std::unique_ptr<LambdaBase> func;
  std::unique_ptr<LambdaBase> input;

  Application(
    std::unique_ptr<LambdaBase> func, std::unique_ptr<LambdaBase> input)
    : func(std::move(func)), input(std::move(input)) {}

  LambdaType getType() const override { return LambdaType::APPLICATION; }

  std::unique_ptr<LambdaBase> copy() const override {
    return std::make_unique<Application>(func->copy(), input->copy());
  }
};

}  // namespace llib
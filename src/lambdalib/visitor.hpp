#pragma once

namespace lambdalib {

class Variable;

class Function;

class Application;

class Visitor {
public:
  virtual ~Visitor() = default;

  virtual void accept(Variable& node) = 0;

  virtual void accept(Function& node) = 0;

  virtual void accept(Application& node) = 0;
};

}  // namespace lambdalib
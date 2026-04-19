#pragma once

#include "nodes.hpp"

#include <string>

namespace llib {

class Parser {
private:
  const std::string source;
  std::size_t index = 0;

  inline char getChar() const {
    return index < source.size() ? source.at(index) : '\0';
  }

  void skipSpaces() {
    while (std::isspace(getChar())) index++;
  }

  std::unique_ptr<LambdaBase> parseVar() {
    std::unique_ptr<LambdaBase> var = std::make_unique<Variable>(getChar());
    index++;
    return var;
  }

  std::unique_ptr<LambdaBase> parseFunc() {
    index++;

    skipSpaces();
    if (!std::isalpha(getChar()))
      throw std::runtime_error("No valid function parameter.");
    std::unique_ptr<LambdaBase> argument = parseVar();

    skipSpaces();
    if (getChar() != '.')
      throw std::runtime_error("No dot after function parameter.");
    index++;

    std::unique_ptr<LambdaBase> body = parseAny();

    return std::make_unique<Function>(
      *((std::unique_ptr<Variable>&)argument), std::move(body));
  }

  std::unique_ptr<LambdaBase> parseApp() {
    index++;

    std::unique_ptr<LambdaBase> left = parseAny();

    skipSpaces();

    std::unique_ptr<LambdaBase> right = parseAny();

    skipSpaces();

    if (getChar() != ')') throw std::runtime_error("Application not closed.");

    index++;

    return std::make_unique<Application>(std::move(left), std::move(right));
  }

  std::unique_ptr<LambdaBase> parseAny() {
    skipSpaces();

    if (std::isalpha(getChar())) return parseVar();

    switch (getChar()) {
      case '&':
        return parseFunc();
      case '(':
        return parseApp();
      default:
        throw std::runtime_error("Not a valid character.");
    }
  }

public:
  Parser(const std::string& source) : source(source) {}

  Parser(std::string&& source) : source(std::move(source)) {}

  std::unique_ptr<LambdaBase> parse() {
    std::unique_ptr<LambdaBase> result = parseAny();

    skipSpaces();

    if (getChar() != '\0')
      throw std::runtime_error("Unexprected trailing characters.");

    return result;
  }
};

inline std::unique_ptr<LambdaBase> parse(const std::string& source) {
  return Parser(source).parse();
}

inline std::unique_ptr<LambdaBase> parse(std::string&& source) {
  return Parser(std::move(source)).parse();
}

}  // namespace llib
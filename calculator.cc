#include "calculator.h"
#include "calculator_exception.h"

#include <array>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stack>
#include <vector>

namespace dev {

IToken::IToken(const std::string& token):token_(token) {}

Operand::Operand(const std::string& token):IToken(token) {
    try {
        value_ = std::stod(token);
    } catch (const std::invalid_argument&) {
        throw InvalidOperandException();
    } catch (const std::out_of_range&) {
        throw OperandOutOfRangeException();
    }
}

double Operand::value() const {
    return value_;
}

Operator::Operator(const std::string& token):IToken(token) {
    // ToDo validate operator and raise exception
    value_ = token[0];
}

char Operator::value() const {
    return value_;
}

bool Calculator::isOperator(const std::string& token) {
    std::array<std::string, 4> operators = {"+", "-", "*", "/"};
    return (std::find(operators.begin(), operators.end(), token) != operators.end());
}

double Calculator::calc(const std::string& expression) {
    std::istringstream iss(expression);
    std::vector<std::string> tokens((std::istream_iterator<std::string>(iss)),
                                     std::istream_iterator<std::string>());

    std::stack<std::string> stkTokens;
    for (auto token : tokens) {
        if (isOperator(token)) {
            Operand operand1 = Operand(stkTokens.top());
            stkTokens.pop();
            Operand operand2 = Operand(stkTokens.top());
            stkTokens.pop();

            stkTokens.push(std::to_string(evalOperation(operand1, operand2, Operator(token))));
        } else {
            stkTokens.push(token);
        }
    }

    return std::stod(stkTokens.top());
}

double Calculator::evalOperation(const Operand& operand1, const Operand& operand2, const Operator& operatr) {
    switch (operatr.value())
    {
    case '+':
        return (operand2.value() + operand1.value());
    case '-':
        return (operand2.value() - operand1.value());
    case '*':
        return (operand2.value() * operand1.value());
    case '/':
        if (operand1.value() == 0) {
            throw DivideByZeroException();
        }
        return (operand2.value() / operand1.value());
    default:
        throw InvalidOperatorException();
    }
}

}  // namespace dev

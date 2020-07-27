#pragma once

#include "icalculator.h"

#include "operand.h"
#include "operator.h"

#include <list>
#include <stack>
#include <vector>

namespace dev {

class Calculator : public ICalculator {
public:
    Calculator() = default;
    ~Calculator() = default;

    double calc(const std::string& expression);
private:
    void parseTokens(const std::string& expression);

    std::list<Operand> operandsList_;
    std::list<std::unique_ptr<Operator>> operatorsList_;
};

}  // namespace dev

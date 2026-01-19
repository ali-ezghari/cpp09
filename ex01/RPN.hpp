#pragma once

#include <iostream>
#include <stack>

class RPN
{
private:
    std::stack<int> st;

public:
    RPN();
    ~RPN();
    RPN(const RPN &instance);
    RPN &operator=(const RPN &instance);
    void calculate(char *str);
};
#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(const RPN &instance)
{
    st = instance.st;
}

RPN &RPN::operator=(const RPN &instance)
{
    if (this != &instance)
    {
        st = instance.st;
    }
    return *this;
}

int checker(char c, char d)
{
    if (isspace(c))
        return false;
    if ((isdigit(c) || c == '-' || c == '/' || c == '+' || c == '*') && d != ' ')
    {
        return true;
    }
    return false;
}

static void performAdd(std::stack<int> &st)
{
    int num1, num2, res;

    if (st.size() < 2)
    {
        throw std::logic_error("Error!");
    }
    num1 = st.top();
    st.pop();
    num2 = st.top();
    st.pop();
    res = num2 + num1;
    st.push(res);
}

static void performMulti(std::stack<int> &st)
{
    int num1, num2, res;

    if (st.size() < 2)
    {
        throw std::logic_error("Error!");
    }
    num1 = st.top();
    st.pop();
    num2 = st.top();
    st.pop();
    res = num2 * num1;
    st.push(res);
}

static void performSub(std::stack<int> &st)
{
    int num1, num2, res;

    if (st.size() < 2)
    {
        throw std::logic_error("Error!");
    }
    num1 = st.top();
    st.pop();
    num2 = st.top();
    st.pop();
    res = num2 - num1;
    st.push(res);
}

static void performDiv(std::stack<int> &st)
{
    int num1, num2, res;

    if (st.size() < 2)
    {
        throw std::logic_error("Error!");
    }
    num1 = st.top();
    st.pop();
    num2 = st.top();
    st.pop();
    res = num2 / num1;
    st.push(res);
}

void RPN::calculate(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        char c = str[i];
        if (str[i + 1] && checker(c, str[i + 1]))
        {
            throw std::logic_error("Error!");
        }
        if (isdigit(c))
        {
            st.push(c - '0');
            continue;
        }

        switch (c)
        {
        case '+':
            performAdd(st);
            break;
        case '-':
            performSub(st);
            break;
        case '*':
            performMulti(st);
            break;
        case '/':
            performDiv(st);
            break;
        default:
            break;
        }
    }
    if (st.size() != 1)
        throw std::logic_error("Error!");
    std::cout << st.top() << std::endl;
}
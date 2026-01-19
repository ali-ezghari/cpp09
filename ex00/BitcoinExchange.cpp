#include "BitcoinExchange.hpp"


void printFormat(const std::string &date, const std::string value, double result)
{
    std::cout << date << " => " << value << " = " << result << std::endl;
}

bool isValidNumber(const std::string &value)
{
    return value.find_first_not_of("0123456789.") == std::string::npos;
}

std::string trim(const std::string &s)
{
    size_t start;
    size_t end;

    start = s.find_first_not_of(' ');
    end = s.find_last_not_of(' ');
    if (start == std::string::npos)
        return "";

    return s.substr(start, end - start + 1);
}
int getDay(const std::string &date)
{
    int day;

    day = atoi(date.substr(date.find_last_of('-') + 1, date.length()).c_str());
    if (day <= 0 || day > 31)
    {
        return (-1);
    }
    return (day);
}
int getMonth(const std::string &date)
{
    int month;

    month = atoi(date.substr(date.find_first_of('-') + 1, date.find_last_of('-')).c_str());
    if (month <= 0 || month > 12)
    {
        return (-1);
    }
    return (month);
}
int getYear(const std::string &date)
{
    int year;

    year = atoi(date.substr(0, date.find_first_of('-')).c_str());
    if (year <= 0)
    {
        return (-1);
    }
    return (year);
}

void isValidDate(const std::string &date)
{
    std::string format = "xxxx-xx-xx";

    if (date.length() != format.length() || !getYear(date) || !getMonth(date) || !getDay(date))
        throw std::logic_error("Invalid date => " + date);

    for (size_t i = 0; i < format.length() - 1; i++)
    {
        if (format[i] == 'x' && !isdigit(date[i]))
            throw std::logic_error("Invalid date => " + date);
        else if (format[i] == '-' && date[i] != '-')
            throw std::logic_error("Invalid date => " + date);
    }
}

void isValidValue(const std::string &value)
{
    if (value.empty())
        throw std::logic_error("Bad Value => " + value);
    else if (value.at(0) == '-')
        throw std::logic_error("Negative Number => " + value);

    if ((count(value.begin(), value.end(), '.')) < 2 && isValidNumber(value) && (value[0] != '.'))
    {
        float num = atof(value.c_str());

        if (num <= 0)
            throw std::logic_error("Too Small Value => " + value);
        else if (num >= 1000)
            throw std::logic_error("Too Large Value => " + value);
    }
    else
        throw std::logic_error("Bad Value => " + value);
}

void parseLine(std::string &line)
{
    std::string date;
    std::string value;

    if (line.find("|") == std::string::npos || line.at(0) == '|')
        throw std::logic_error("Bad input => " + line);

    line = trim(line);
    date = trim(line.substr(0, line.find("|")));
    value = trim(line.substr(line.find("|") + 1, line.length() - 1));

    isValidDate(date);
    isValidValue(value);
}

bool handleOutOfRangeDate(const std::string &date, const std::string &value, std::map<std::string, float> &dataSet)
{
    std::map<std::string, float>::iterator first, last;
    int year;
    int month;
    int day;

    year = getYear(date);
    month = getMonth(date);
    day = getDay(date);
    first = dataSet.begin();
    last = dataSet.end();
    --last;

    if (year < getYear(first->first) || (year == getYear(first->first) && month < getMonth(first->first)) || (year == getYear(first->first) && month >= getMonth(first->first) && day < getDay(first->first)))
    {
        printFormat(date, value, atof(value.c_str()) * first->second);
        return true;
    }
    else if (year > getYear(last->first) || (year == getYear(last->first) && month > getMonth(last->first)) || (year == getYear(last->first) && month <= getMonth(last->first) && day > getDay(last->first)))
    {
        printFormat(date, value, atof(value.c_str()) * last->second);
        return true;
    }
    return false;
}

void printNearestDate(const std::string &date, const std::string &value, std::map<std::string, float> &dataSet)
{
    std::map<std::string, float>::iterator it;
    std::map<std::string, float>::iterator lowest;
    int dateDay;
    int dataSetDay;

    if (handleOutOfRangeDate(date, value, dataSet))
    {
        return;
    }

    dateDay = atoi(date.substr(date.find_last_of('-') + 1, date.length()).c_str());
    for (it = dataSet.begin(); it != dataSet.end(); it++)
    {
        if (it->first.substr(0, it->first.find_last_of('-')) == date.substr(0, date.find_last_of('-')))
            break;
    }

    if (dateDay == 0)
    {
        --it;
        printFormat(date, value, atof(value.c_str()) * it->second);
        return;
    }
    lowest = it;
    while (it != dataSet.end() && it->first.substr(0, it->first.find_last_of('-')) == date.substr(0, date.find_last_of('-')))
    {
        dataSetDay = atoi(it->first.substr(it->first.find_last_of('-') + 1, it->first.length()).c_str());

        if (dataSetDay > dateDay)
        {
            break;
        }
        lowest = it;
        it++;
    }

    printFormat(date, value, atof(value.c_str()) * lowest->second);
}

void printOutput(const std::string &date, const std::string &value, std::map<std::string, float> &dataSet)
{
    std::map<std::string, float>::iterator it = dataSet.find(date);

    if (it != dataSet.end())
    {
        printFormat(date, value, atof(value.c_str()) * it->second);
    }
    else
    {
        printNearestDate(date, value, dataSet);
    }
}
bool isValidFirstLine(const std::string &line)
{
    std::string str1;
    std::string str2;

    str1 = trim(line.substr(0, line.find("|")));
    str2 = trim(line.substr(line.find("|") + 1, line.length()));

    if (str1 + "|" + str2 == "date|value")
        return true;
    return false;
}
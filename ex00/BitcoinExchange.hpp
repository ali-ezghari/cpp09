#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

void printFormat(const std::string &date, const std::string value, double result);

bool isValidNumber(const std::string &value);

std::string trim(const std::string &s);
int getDay(const std::string &date);
int getMonth(const std::string &date);
int getYear(const std::string &date);

void isValidDate(const std::string &date);
void isValidValue(const std::string &value);

void parseLine(std::string &line);

bool handleOutOfRangeDate(const std::string &date, const std::string &value, std::map<std::string, float> &dataSet);

void printNearestDate(const std::string &date, const std::string &value, std::map<std::string, float> &dataSet);

void printOutput(const std::string &date, const std::string &value, std::map<std::string, float> &dataSet);
bool isValidFirstLine(const std::string &line);
#pragma once

#include <iostream>
#include <vector>
#include <string>

std::vector<double> ReadVector(std::istream& input);
void ProcessVector(std::vector<double>& vector);
void PrintVector(std::ostream& output, std::vector<double>& vector);
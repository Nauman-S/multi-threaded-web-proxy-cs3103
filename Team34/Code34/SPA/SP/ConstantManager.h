#pragma once

# include <vector>
class ConstantManager {
public:
	void addConstant(double);

	std::vector<double> getConstants();

protected:
	std::vector<double>* constants;
};
#pragma once

# include <vector>
class ConstantManager {
public:
	void addConstant(int&);

	std::vector<int> getConstants();

protected:
	std::vector<int> constants;
};
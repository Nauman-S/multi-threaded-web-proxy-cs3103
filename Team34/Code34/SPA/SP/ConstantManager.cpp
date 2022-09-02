# include "ConstantManager.h"

void ConstantManager::addConstant(double num) {
	constants->push_back(num);
}

std::vector<double> ConstantManager::getConstants() {
	return *constants;
}
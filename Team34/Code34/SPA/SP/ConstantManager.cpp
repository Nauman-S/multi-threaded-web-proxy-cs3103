# include "ConstantManager.h"

void ConstantManager::addConstant(int& num) {
	constants.push_back(num);
}

std::vector<int> ConstantManager::getConstants() {
	return constants;
}

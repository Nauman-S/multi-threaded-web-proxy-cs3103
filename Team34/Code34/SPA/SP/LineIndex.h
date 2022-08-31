#pragma once

class LineIndex {
public:
	void setLineNum(int n) {
		lineNum = n;
	}

	int getLineNum() {
		return lineNum;
	}

protected:
	int lineNum;
};
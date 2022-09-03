#pragma once

class LineIndex {
public:
	void setLineNum(int);

	int getLineNum();

	bool operator < (const LineIndex& c) const
	{
		return lineNum < c.lineNum;
	}

protected:
	int lineNum;
};
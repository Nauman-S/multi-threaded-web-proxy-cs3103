#pragma once

class LineIndex {
public:
	void SetLineNum(int);

	int GetLineNum();

	bool operator < (const LineIndex& c) const
	{
		return lineNum < c.lineNum;
	}

protected:
	int lineNum;
};
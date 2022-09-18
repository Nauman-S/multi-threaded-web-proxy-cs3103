#pragma once

#include <map>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class TopoCycle {
public:
	bool CheckCycle(vector<pair<string, string>>, vector<string>);

	void Dfs(int);

	bool HaveCycle(int, int);

	void AddEdge(int, int);

	void Init(int);
private:
	stack<int> s;
	vector<int> tsort;
	vector<vector<int>> adj;
	vector<int> visited;
};

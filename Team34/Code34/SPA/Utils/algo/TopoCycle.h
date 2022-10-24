#pragma once

#include <map>
#include <string>
#include <stack>
#include <vector>

#include "../type/TypeDef.h"

using namespace std;

class TopoCycle {
public:
	bool CheckCycle(vector<pair<Procedure, Procedure>>, vector<Procedure>);
	vector<Procedure> GenerateList(vector<pair<Procedure, Procedure>>, vector<Procedure>);

private:
	void Dfs(int);
	bool HaveCycle();
	void AddEdge(int, int);
	bool Init(vector<pair<Procedure, Procedure>>, vector<Procedure>);
	stack<int> s;
	vector<int> tsort;
	vector<vector<int>> adj;
	vector<int> visited;
	map<Procedure, int> mapping;
	int num_edges;
	int num_nodes;
};

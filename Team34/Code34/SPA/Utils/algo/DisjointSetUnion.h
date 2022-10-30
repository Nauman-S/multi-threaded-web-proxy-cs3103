#pragma once

#include <string>
#include <vector>
#include <utility>

#include "../../QPS/reference/Ref.h"

using namespace std;
class DisjointSetUnion
{
private:
	int Find(vector<int>&, int);
 
	void Union( vector<int>&, vector<int>&, int, int );

public:
	vector<vector<string>> GetConnectedComponents(vector<pair<string, string>> edges, vector<string> nodes);
};


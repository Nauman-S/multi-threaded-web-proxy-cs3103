#include "TopoCycle.h"
#include <stack>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;


void TopoCycle::Dfs(int u) {
	// Set the vertex as visited
	visited[u] = 1;

	for (auto it : adj[u]) {

		// Visit connected vertices
		if (visited[it] == 0)
			Dfs(it);
	}

	// Push into the stack on
	// complete visit of vertex
	s.push(u);
}

void TopoCycle::AddEdge(int u, int v)
{
	adj[u].push_back(v);
}

bool TopoCycle::HaveCycle(int m, int n)
{
	// Stores the position of
	// vertex in topological order
	unordered_map<int, int> pos;
	int index = 0;

	// Pop all elements from stack
	while (!s.empty()) {
		pos[s.top()] = index;

		// Push element to get
		// Topological Order
		tsort.push_back(s.top());

		index += 1;

		// Pop from the stack
		s.pop();
	}

	for (int i = 0; i < n; i++) {
		for (auto it : adj[i]) {

			// If parent vertex
			// does not appear first
			if (pos[i] > pos[it]) {

				// Cycle exists
				return true;
			}
		}
	}

	// Return false if cycle
	// does not exist
	return false;
}

bool TopoCycle::CheckCycle(map<string, string> edges, vector<string> nodes) {
	int num_nodes = nodes.size();
	int num_edges = edges.size();
	cout << num_nodes << num_edges << endl;
	Init(num_nodes);
	map<string, int> mapping;
	int temp = 0;
	for (auto p : nodes) {
		mapping[p] = temp++;
	}
	for (auto const& x : edges) {
		if (x.first == x.second) {
			return true;
		}
		AddEdge(mapping[x.first], mapping[x.second]);
	}

	for (int i = 0; i < num_nodes; i++) {
		if (visited[i] == 0) {
			Dfs(i);
		}
	}
	return HaveCycle(num_edges, num_nodes);
}

void TopoCycle::Init(int num_nodes) {
	for (int i = 0; i < num_nodes; i++) {
		vector<int> tmp;
		adj.push_back(tmp);
		visited.push_back(0);
	}
}
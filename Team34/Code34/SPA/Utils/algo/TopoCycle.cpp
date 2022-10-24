#include "TopoCycle.h"
#include <stack>
#include <stdexcept>
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

bool TopoCycle::HaveCycle()
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

	for (int i = 0; i < num_nodes; i++) {
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

bool TopoCycle::CheckCycle(vector<pair<Procedure, Procedure>> edges, vector<Procedure> nodes) {

	if (!Init(edges, nodes)) {
		return true;
	}
	for (int i = 0; i < num_nodes; i++) {
		if (visited[i] == 0) {
			Dfs(i);
		}
	}

	return HaveCycle();
}

bool TopoCycle::Init(vector<pair<Procedure, Procedure>> edges, vector<Procedure> nodes) {
    num_nodes = nodes.size();
	num_edges = edges.size();
	for (int i = 0; i < num_nodes; i++) {
		vector<int> tmp;
		adj.push_back(tmp);
		visited.push_back(0);
	}
	int temp = 0;
	for (auto p : nodes) {
		mapping[p] = temp++;
	}
	for (auto x : edges) {
		if (x.first == x.second) {
			return false;
		}
		AddEdge(mapping[x.first], mapping[x.second]);
	}
	return true;
}

vector<Procedure> TopoCycle::GenerateList(vector<pair<Procedure, Procedure>> edges, vector<Procedure> nodes) {
	if (CheckCycle(edges, nodes)) {
		throw exception("cycle detected");
	}
	else {
		vector<Procedure> res;
		for (auto n : tsort) {
			for (auto const& x : mapping) {
				if (x.second == n) {
					res.push_back(x.first);
					break;
				}
			}
		}
		return res;
	}
}
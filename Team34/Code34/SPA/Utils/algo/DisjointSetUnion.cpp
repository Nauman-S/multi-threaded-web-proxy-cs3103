#include "DisjointSetUnion.h"

#include <unordered_map>
using namespace std;

vector<vector<string>> DisjointSetUnion::GetConnectedComponents(vector<pair<string, string>> edges, vector<string> nodes) {
	int num_nodes = nodes.size();
	int num_edges = edges.size();

	unordered_map<string, int> map;
	unordered_map<int, string> map_back;

	//map nodes to int
	int integer_mapping_of_node = 0;
	for (;integer_mapping_of_node < num_nodes; integer_mapping_of_node++) {
		map_back[integer_mapping_of_node] = nodes.at(integer_mapping_of_node);
		map[nodes.at(integer_mapping_of_node)] = integer_mapping_of_node;
	}

	vector<int> parent(num_nodes);
	vector<int> size(num_nodes);

	//each node is its own parent
	integer_mapping_of_node--;
	for (;integer_mapping_of_node > -1; integer_mapping_of_node--) {

		parent[integer_mapping_of_node] = integer_mapping_of_node;
		size[integer_mapping_of_node] = 1;
	}

	for (pair<string, string> edge : edges) {
		Union(parent, size, map[edge.first], map[edge.second]);
	}

	//for each node set its root as parent
	integer_mapping_of_node++;
	for (; integer_mapping_of_node < num_nodes; integer_mapping_of_node++) {
		parent[integer_mapping_of_node] = Find(parent, integer_mapping_of_node);
	} 
	//extract components from graph
	unordered_map <int, vector<int>> connected_component_map;
	integer_mapping_of_node--;
	for (; integer_mapping_of_node > -1;integer_mapping_of_node--) {
		connected_component_map[parent[integer_mapping_of_node]].push_back(integer_mapping_of_node);
	}

	//map nodes back to string
	vector<vector<string>> connected_component_vector;

	for (auto it : connected_component_map) {
		vector <string> connected_component;
		for (auto node_as_int : it.second) {
			connected_component.push_back(map_back[node_as_int]);
		}
		connected_component_vector.push_back(connected_component);
	}
	return connected_component_vector;
}

//Union by Size Optimization
void DisjointSetUnion::Union(vector<int> &parent, vector<int> &size, int node1, int node2) {
	node1 = Find(parent, node1);
	node2 = Find(parent, node2);
	if (node1 != node2) {
		int temp;
		if (size[node1] < size[node2]) {
			temp = node2;
			node2 = node1;
			node1 = node2;
		}

		parent[node2] = node1;
		size[node1] += size[node2];
	}
}

//Path Compression Optimization
int DisjointSetUnion::Find(vector<int>& parent, int node) {
	if (parent[node] == node) {
		return node;
	}
	return parent[node] = Find(parent, parent[node]);
}





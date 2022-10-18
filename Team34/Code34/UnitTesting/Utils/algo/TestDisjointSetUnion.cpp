#include "stdafx.h"
#include "CppUnitTest.h"

#include"../SPA/Utils/algo/DisjointSetUnion.h"

#include <vector>
#include <string>
#include <unordered_set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;
using std::string;
using std::pair;
using std::unordered_set;

namespace UnitTesting
{
	TEST_CLASS(TestDisjointSetUnion)
	{
	private:
	public:

		TEST_METHOD(TestDisjointSetUnionSimpleCase)
		{
			vector<string> nodes = { "alpha", "bravo", "charlie", "delta", "echo"};

			pair edge1 = std::make_pair<string, string> ("alpha", "bravo");
			pair edge2 = std::make_pair<string, string> ("bravo", "charlie");
			pair edge3 = std::make_pair<string, string>("echo", "delta");
			vector<pair<string, string>> edges = { edge1, edge2, edge3 };

			DisjointSetUnion union_find;
			vector<vector<string>> connected_components = union_find.GetConnectedComponents( edges, nodes);

			unordered_set<string> correct_component_1 = {"alpha", "bravo", "charlie"};
			unordered_set<string> correct_component_2 = { "echo", "delta" };

			bool isValid = true;
			for (vector<string> vector : connected_components) {
				Assert::IsTrue(vector.size() > 0);
				if (correct_component_1.find(vector.at(0)) != correct_component_1.end()) {
					for (string node : vector) {
						Assert::IsTrue(correct_component_1.find(node) != correct_component_1.end());
						correct_component_1.erase(node);
					}
				} else if (correct_component_2.find(vector.at(0)) != correct_component_2.end()) {
					for (string node : vector) {
						Assert::IsTrue(correct_component_2.find(node) != correct_component_2.end());
						correct_component_2.erase(node);
					}
				}
				else {
					isValid = false;
				}
			}

			Assert::IsTrue(isValid);
			Assert::IsTrue(correct_component_1.size() == 0);
			Assert::IsTrue(correct_component_2.size() == 0);
		}

		TEST_METHOD(TestDisjointSetUnionComplexCase)
		{
			vector<string> nodes = { "alpha", "bravo", "charlie", "delta", "echo", "foxtrot", "golf", "hotel", "india", "juliet", "kilo", "lima", "zulu"};
			pair edge1 = std::make_pair<string, string>("alpha", "charlie");
			pair edge2 = std::make_pair<string, string>("echo", "alpha");
			pair edge3 = std::make_pair<string, string>("charlie", "delta");
			pair edge4 = std::make_pair<string, string>("golf", "hotel");
			pair edge5 = std::make_pair<string, string>("foxtrot", "bravo");
			pair edge6 = std::make_pair<string, string>("hotel", "india");
			pair edge7 = std::make_pair<string, string>("juliet", "kilo");
			pair edge8 = std::make_pair<string, string>("kilo", "lima");
			pair edge9 = std::make_pair<string, string>("delta", "foxtrot");
			pair edge10 = std::make_pair<string, string>("india", "lima");
			pair edge11 = std::make_pair<string, string>("bravo", "charlie");
			pair edge12 = std::make_pair<string, string>("bravo", "foxtrot");
			vector<pair<string, string>> edges = { edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10, edge11, edge12 };

			DisjointSetUnion union_find;
			vector<vector<string>> connected_components = union_find.GetConnectedComponents(edges, nodes);

			unordered_set<string> correct_component_1 = { "alpha", "bravo", "charlie", "delta", "echo", "foxtrot" };
			unordered_set<string> correct_component_2 = { "golf", "hotel", "india", "juliet", "kilo", "lima" };
			unordered_set<string> correct_component_3 = { "zulu" };

			bool isValid = true;
			for (vector<string> vector : connected_components) {
				Assert::IsTrue(vector.size() > 0);
				if (correct_component_1.find(vector.at(0)) != correct_component_1.end()) {
					for (string node : vector) {
						Assert::IsTrue(correct_component_1.find(node) != correct_component_1.end());
						correct_component_1.erase(node);
					}
				}
				else if (correct_component_2.find(vector.at(0)) != correct_component_2.end()) {
					for (string node : vector) {
						Assert::IsTrue(correct_component_2.find(node) != correct_component_2.end());
						correct_component_2.erase(node);
					}
				}
				else if (correct_component_3.find(vector.at(0)) != correct_component_3.end()) {
					for (string node : vector) {
						Assert::IsTrue(correct_component_3.find(node) != correct_component_3.end());
						correct_component_3.erase(node);
					}
				}
				else {
					isValid = false;
				}
			}

			Assert::IsTrue(isValid);
			Assert::IsTrue(correct_component_1.size() == 0);
			Assert::IsTrue(correct_component_2.size() == 0);
			Assert::IsTrue(correct_component_3.size() == 0);
		}

		TEST_METHOD(TestDisjointSetUnionRepeatedEdges)
		{
			vector<string> nodes = { "alpha", "bravo", "charlie", "delta", "echo", "foxtrot", "golf", "hotel", "india", "juliet", "kilo", "lima", "zulu" };
			pair edge1 = std::make_pair<string, string>("alpha", "charlie");
			pair edge2 = std::make_pair<string, string>("echo", "alpha");
			pair edge3 = std::make_pair<string, string>("charlie", "delta");
			pair edge4 = std::make_pair<string, string>("golf", "hotel");
			pair edge5 = std::make_pair<string, string>("foxtrot", "bravo");
			pair edge6 = std::make_pair<string, string>("hotel", "india");
			pair edge7 = std::make_pair<string, string>("juliet", "kilo");
			pair edge8 = std::make_pair<string, string>("kilo", "lima");
			pair edge9 = std::make_pair<string, string>("delta", "foxtrot");
			pair edge10 = std::make_pair<string, string>("india", "lima");
			pair edge11 = std::make_pair<string, string>("bravo", "charlie");
			pair edge12 = std::make_pair<string, string>("bravo", "foxtrot");
			pair edge13 = std::make_pair<string, string>("kilo", "juliet");
			pair edge14 = std::make_pair<string, string>("delta", "charlie");
			pair edge15 = std::make_pair<string, string>("india", "lima");
			vector<pair<string, string>> edges = { edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10, edge11, edge12, edge13, edge14, edge15 };

			DisjointSetUnion union_find;
			vector<vector<string>> connected_components = union_find.GetConnectedComponents(edges, nodes);

			unordered_set<string> correct_component_1 = { "alpha", "bravo", "charlie", "delta", "echo", "foxtrot" };
			unordered_set<string> correct_component_2 = { "golf", "hotel", "india", "juliet", "kilo", "lima" };
			unordered_set<string> correct_component_3 = { "zulu" };

			bool isValid = true;
			for (vector<string> vector : connected_components) {
				Assert::IsTrue(vector.size() > 0);
				if (correct_component_1.find(vector.at(0)) != correct_component_1.end()) {
					for (string node : vector) {
						Assert::IsTrue(correct_component_1.find(node) != correct_component_1.end());
						correct_component_1.erase(node);
					}
				}
				else if (correct_component_2.find(vector.at(0)) != correct_component_2.end()) {
					for (string node : vector) {
						Assert::IsTrue(correct_component_2.find(node) != correct_component_2.end());
						correct_component_2.erase(node);
					}
				}
				else if (correct_component_3.find(vector.at(0)) != correct_component_3.end()) {
					for (string node : vector) {
						Assert::IsTrue(correct_component_3.find(node) != correct_component_3.end());
						correct_component_3.erase(node);
					}
				}
				else {
					isValid = false;
				}
			}

			Assert::IsTrue(isValid);
			Assert::IsTrue(correct_component_1.size() == 0);
			Assert::IsTrue(correct_component_2.size() == 0);
			Assert::IsTrue(correct_component_3.size() == 0);

		}
	};
}
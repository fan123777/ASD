#include "Graph.h"

using namespace std;

namespace nsAlgorithmsOnGraphs
{
	namespace nsGraphPropertiesTypes
	{
		namespace nsGraph
		{
			std::vector<Edge> getDFSGraphEdges(int& v)
			{
				vector<Edge> edges = {
					{ 0, 2 }, { 0, 5 },
					{ 1, 7 },
					{ 2, 6 },
					{ 3, 4 }, { 3, 5 },
					{ 4, 5 }, { 4, 6 }, { 4, 7 },
				};
				v = 8;
				return edges;
			}

			std::vector<Edge> getSearchGraphEdges(int& v)
			{
				vector<Edge> edges = {
					{ 0, 1 }, { 0, 9 },
					{ 1, 4 }, { 1, 9 },
					{ 2, 7 }, { 2, 10 }, { 2, 12 },
					{ 3, 12 },
					{ 5, 12 },
					{ 6, 10 }, { 6, 12 },
					{ 7, 10 },
					{ 8, 11 }
				};
				v = 13;
				return edges;
			}

			std::vector<Edge> getBridgeGraphEdges(int& v)
			{
				vector<Edge> edges = {
					{ 0, 1 }, { 0, 5 }, { 0, 6 },
					{ 1, 2 },
					{ 2, 6 },
					{ 3, 4 }, { 3, 5 },
					{ 4, 5 }, { 4, 9 }, { 4, 11 },
					{ 6, 7 },
					{ 7, 8 }, { 7, 10 },
					{ 8, 10 },
					{ 9, 11 },
					{ 11, 12 }
				};
				v = 13;
				return edges;
			}

			std::vector<Edge> getBFSGraphEdges(int& v)
			{
				vector<Edge> edges = {
					{ 0, 2 }, { 0, 5 }, { 0, 7 },
					{ 1, 7 },
					{ 2, 6 },
					{ 3, 4 }, { 3, 5 },
					{ 4, 5 }, { 4, 6 }, { 4, 7 },
				};
				v = 8;
				return edges;
			}

			std::vector<Edge> getDigraphEdges(int& v)
			{
				vector<Edge> edges = {
					{ 0, 0 }, { 0, 5 }, { 0, 1 }, { 0, 6 },
					{ 1, 1 },
					{ 2, 2 }, { 2, 0 }, { 2, 3 },
					{ 3, 3 }, { 3, 5 }, { 3, 2 },
					{ 4, 4 }, { 4, 3 }, { 4, 11 }, { 4, 2 },
					{ 5, 5 }, { 5, 4 },
					{ 6, 6 }, { 6, 9 }, { 6, 4 },
					{ 7, 7 }, { 7, 6 }, { 7, 8 },
					{ 8, 8 }, { 8, 7 }, { 8, 9 },
					{ 9, 9 }, { 9, 11 }, { 9, 10 },
					{ 10, 10 }, { 10, 12 },
					{ 11, 11 }, { 11, 12 },
					{ 12, 12 }, { 12, 9 }
				};
				v = 13;
				return edges;
			}
		}

		namespace nsChapter
		{
			namespace nsSparseMultiGraph
			{
				void randE(Graph &G, int E)
				{
					for (int i = 0; i < E; i++)
					{
						int v = int(G.V()*rand() / (1.0 + RAND_MAX));
						int w = int(G.V()*rand() / (1.0 + RAND_MAX));
						G.insert(Edge(v, w));
					}
				}

				void randG(Graph &G, int E)
				{
					double p = 2.0 * E / G.V() / (G.V() - 1);
					for (int i = 0; i < G.V(); i++)
					for (int j = 0; j < i; j++)
					if (rand() < p * RAND_MAX)
						G.insert(Edge(i, j));
				}
			}
		}
	}
}

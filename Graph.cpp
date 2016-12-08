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

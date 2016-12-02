#include "Graph.h"

using namespace std;

namespace nsAlgorithmsOnGraphs
{
	namespace nsGraphPropertiesTypes
	{
		namespace nsGraph
		{
		
		}

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
		}
	}
}

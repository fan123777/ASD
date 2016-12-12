#include "DigraphsAndDirectedAcyclicGraph.h"
#include "Graph.h"

using namespace std;

namespace nsAlgorithmsOnGraphs
{
	namespace nsDigraphsAndDirectedAcyclicGraph
	{
		void main()
		{
			test();
		}

		void test()
		{
			using namespace nsGraphPropertiesTypes::nsGraph;

			int v = 0;
			auto edges = getDigraphEdges(v);

			Graph<DenseImpl> G(v, true);
			addEdges(G, edges);
			// showAll(G);

			Graph<SparseImpl> G1(v, true);
			addEdges(G1, edges);
			// showAll(G1);

			Graph<DenseImpl> G2(v, true);
			reverse(G, G2);
			showAll(G2);
		}
	}
}

#include "MinimumSpanningTree.h"
#include "Graph.h"

using namespace std;

namespace nsAlgorithmsOnGraphs
{
	namespace nsMinimumSpanningTree
	{
		void main()
		{
			test();
		}

		void test()
		{
			using namespace nsGraphPropertiesTypes::nsGraph;

			int v = 0;
			auto edges = getPrimGraphEdges(v);

			WGraph<WDenseImpl<WEdge>,WEdge> wG(v);
			addWEdges(wG, edges);
			wShowAll(wG);

			// auto A = wG.getIterator(5);
			// auto edges = getWEdges<WGraph<WDenseImpl<WEdge>, WEdge>, WEdge>(wG);


			WGraph<WSparseImpl<WEdge>, WEdge> wG1(v);
			addWEdges(wG1, edges);
			wShowAll(wG1);

			// auto A1 = wG1.getIterator(5);
			// auto edges1 = getWEdges<WGraph<WSparseImpl<WEdge>, WEdge>, WEdge>(wG1);

			PMST<WGraph<WDenseImpl<WEdge>, WEdge>, WEdge> mst(wG);
			mst.show();
		}
	}
}

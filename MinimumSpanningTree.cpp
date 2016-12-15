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
			WGraph<WDenseImpl<WEdge>,WEdge> wG(10);
			auto A = wG.getIterator(5);
			auto edges = wEdges<WGraph<WDenseImpl<WEdge>, WEdge>, WEdge>(wG);
		}
	}
}

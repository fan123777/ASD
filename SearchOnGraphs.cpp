#include "SearchOnGraphs.h"
#include "Graph.h"

using namespace std;

namespace nsAlgorithmsOnGraphs
{
	namespace nsSearchOnGraphs
	{
		void main()
		{
			test();
		}

		void test()
		{
			using namespace nsGraphPropertiesTypes::nsGraph;
			int v = 0;
			auto edges = getDFSGraphEdges(v);

			Graph<DenseImpl> G(v);
			addEdges(G, edges);
			DFS<Graph<DenseImpl>> dfs(G, 0);
			int c = dfs.count();

			for (int i = 0; i < G.V(); i++)
				cout << dfs[i] << " ";
			cout << endl;
			show(G);

			Graph<SparseImpl> G1(v);
			addEdges(G1, edges);
			DFS<Graph<SparseImpl>> dfs1(G1, 0);
			c = dfs1.count();

			for (int i = 0; i < G1.V(); i++)
				cout << dfs1[i] << " ";
			cout << endl;
			show(G1);
		}
	}
}

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
			sDFS<Graph<DenseImpl>> dfs(G, 0);
			int count= dfs.count();

			for (int i = 0; i < G.V(); i++)
				cout << dfs[i] << " ";
			cout << endl;
			show(G);

			Graph<SparseImpl> G1(v);
			addEdges(G1, edges);
			sDFS<Graph<SparseImpl>> dfs1(G1, 0);
			count = dfs1.count();

			for (int i = 0; i < G1.V(); i++)
				cout << dfs1[i] << " ";
			cout << endl;
			show(G1);


			edges = getSearchGraphEdges(v);
			Graph<DenseImpl> G2(v);

			DFS<Graph<DenseImpl>> d(G2);
			CC<Graph<DenseImpl>> c(G2);
			Euler<Graph<DenseImpl>> e(G2);
			EC<Graph<DenseImpl>> ec(G2);
		}
	}
}

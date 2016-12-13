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
			// showAll(G);
			sDFS<Graph<DenseImpl>> dfs(G, 0);
			int count = dfs.count();
			// dfs.show();
			
			Graph<SparseImpl> G1(v);
			addEdges(G1, edges);
			// showAll(G1);
			DFS<Graph<SparseImpl>> dfs1(G1);
			// dfs1.show();
			
			edges = getSearchGraphEdges(v);
			Graph<DenseImpl> G2(v);
			addEdges(G2, edges);
			showAll(G2);
			DFS<Graph<DenseImpl>> d(G2);
			d.show();

			CC<Graph<DenseImpl>> c(G2);
			int cc = c.count();
			bool connected = c.connect(1, 6);

			Euler<Graph<DenseImpl>> e(G2);
			BI<Graph<DenseImpl>> bi(G2);
			EC<Graph<DenseImpl>> ec(G2);

			edges = getBFSGraphEdges(v);
			Graph<DenseImpl> G3(v);
			addEdges(G3, edges);
			BFS<Graph<DenseImpl>> b(G3);
			// Например, после построения объекта bfs класса BFS<Graph> может использовать следующий программный код для распечатки пути, ведущего из w в v:
			// for (int t = 0; t != 3; t = b.ST(t))
			//	cout << t << "-";
			// cout << 3 << endl;

			PFS<Graph<DenseImpl>> pfs(G3);
		}
	}
}

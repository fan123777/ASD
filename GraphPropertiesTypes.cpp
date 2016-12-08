#include "GraphPropertiesTypes.h"
#include <iostream>
#include "Graph.h"

using namespace std;

namespace nsAlgorithmsOnGraphs
{
	namespace nsGraphPropertiesTypes
	{
		// using namespace nsGraph;

		void main()
		{
			program17_6();
			test();
		}

		void program17_6()
		{
			/*int V = 5;
			Graph G(V);
			IO<Graph>::scan(G);
			if (V < 20)
			IO<Graph>::show(G);
			cout << G.E() << " edges ";
			CC<Graph> Gcc(G);
			cout << Gcc.count() << " components" << endl;*/
		}

		void test()
		{
			using namespace nsGraph;

			int V = 7;
			Graph<DenseImpl> G(V);
			Graph<SparseImpl> G1(V);

			vector<Edge> edges1 = { { 0, 3 }, { 0, 4 }, { 2, 1 }, { 3, 2 } };
			vector<Edge> edges =
			{
				{ 0, 5 }, { 0, 1 }, { 0, 2 }, { 0, 6 },
				{ 1, 0 }, { 1, 2 }, {1, 3},
				{ 2, 0 }, { 2, 1 }, { 2, 3 }, {2, 4},
				{ 3, 1 }, { 3, 2 }, { 3, 4 }, {3, 5},
				{ 4, 2 }, { 4, 3 }, { 4, 5 }, { 4, 6 },
				{ 5, 0 }, { 5, 3 }, { 5, 4 },
				{ 6, 0 }, { 6, 4 },
			};

			// scanEZ(G);
			addEdges(G, edges);
			addEdges(G1, edges1);

			// randE(G, 20);

			show(G);
			showEdges(G);
			showAdjacencyMatrix(G);

			// cout << endl;

			// show(G1);
			// showEdges(G1);
			// showAdjacencyMatrix(G1);

			cout << G.E() << " edges ";

			cout << endl;
			Degree<Graph<DenseImpl>> d(G);
			for (int i = 0; i < G.V(); i++)
				cout << d[i] << " ";

			sPath<Graph<DenseImpl>> p(G);
			bool hamiltonPath = p.findHamiltonPath(0, 6);

			sPath<Graph<SparseImpl>> p1(G1);
			bool simplePath = p1.findSimplePath(3, 4);

			cout << endl;
		}
	}
}

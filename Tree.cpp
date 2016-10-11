#include "Tree.h"

namespace nsDataStructures
{
	namespace nsRecursionAndTrees
	{
		void MyTraverseG(int k, void visit(int), int visited[], MyGlink adj[])
		{
			visit(k);
			visited[k] = 1;
			for (MyGlink t = adj[k]; t != 0; t = t->next)
			if (!visited[t->v])
				MyTraverseG(t->v, visit, visited, adj);
		}

		void widthTraverseG(int k, void visit(int), int visited[], MyGlink adj[])
		{
			nsAbstractDataTypes::nsListQueue::Queue<int> q;
			q.put(k);
			while (!q.empty())
			if (visited[k = q.get()] = 0)
			{
				visit(k); visited[k] = 1;
				for (MyGlink t = adj[k]; t != 0; t = t->next)
					if (visited[t->v] == 0)
						q.put(t->v);
			}
		}
	}
}

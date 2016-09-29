#include "UnionFind.h"

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		// Программа 4.11 Реализация АТД "Отношения эквивалентности"
		UnionFind::UnionFind(int N)
		{
			id = new int[N];
			sz = new int[N];
			for (int i = 0; i < N; i++)
			{
				id[i] = i;
				sz[i] = 1;
			}
		}

		UnionFind::~UnionFind()
		{
			delete[] id;
			delete[] sz;
		}

		int UnionFind::find(int p, int q)
		{
			return (find(p) == find(q));
		}

		void UnionFind::unite(int p, int q)
		{
			int i = find(p), j = find(q);
			if (i == j)
				return;
			if (sz[i] < sz[j])
			{
				id[i] = j;
				sz[j] += sz[i];
			}
			else
			{
				id[j] = i;
				sz[i] += sz[j];
			}
		}

		int UnionFind::find(int x)
		{
			while (x != id[x])
				x = id[x];
			return x;
		}
	}
}

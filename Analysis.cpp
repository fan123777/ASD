#include "Analysis.h"
#include <iostream>

using namespace std;

namespace nsAnalysis
{
	void main()
	{
		const int N = 7;
		int a[N][2] = { { 1, 2 }, { 2, 3 }, { 1, 3 }, { 1, 5 }, { 4, 6 }, { 1, 3 }, { 6, 4 } };

		program1(N, a);
		cout << endl;

		program2(N, a);
		cout << endl;

		program3(N, a);
		cout << endl;

		program4(N, a);
		cout << endl;
	}

	void program1(const int N, int a[][2])
	{
		int i, j, p, q;
		int* id = new int[N];
		for (i = 0; i < N; i++)
			id[i] = i;

		for (j = 0; j < N; j++)
		{
			p = a[j][0];
			q = a[j][1];

			int t = id[p];
			if (t == id[q])
				continue;

			for (i = 0; i < N; i++)
			if (id[i] == t)
				id[i] = id[q];

			cout << " " << p << " " << q << endl;
		}

		delete[] id;
	}
	
	void program2(int N, int a[][2])
	{
		int i, j, k, p, q;
		int* id = new int[N];
		for (i = 0; i < N; i++)
			id[i] = i;

		for (k = 0; k < N; k++)
		{
			p = a[k][0];
			q = a[k][1];

			for (i = p; i != id[i]; i = id[i]);
			for (j = q; j != id[j]; j = id[j]);
			if (i == j)
				continue;

			id[i] = j;

			cout << " " << p << " " << q << endl;
		}

		delete[] id;
	}

	void program3(int N, int a[][2])
	{
		int i, j, k, p, q;
		int* id = new int[N];
		int* sz = new int[N];
		for (i = 0; i < N; i++)
		{
			id[i] = i;
			sz[i] = 1;
		}

		for (k = 0; k < N; k++)
		{
			p = a[k][0];
			q = a[k][1];

			for (i = p; i != id[i]; i = id[i]);
			for (j = q; j != id[j]; j = id[j]);
			if (i == j)
				continue;

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

			cout << " " << p << " " << q << endl;
		}

		delete[] id;
		delete[] sz;
	}

	void program4(int N, int a[][2])
	{
		int i, j, k, p, q;
		int* id = new int[N];
		int* sz = new int[N];
		for (i = 0; i < N; i++)
		{
			id[i] = i;
			sz[i] = 1;
		}

		for (k = 0; k < N; k++)
		{
			p = a[k][0];
			q = a[k][1];

			for (i = p; i != id[i]; i = id[i])
				id[i] = id[id[i]];
			for (j = q; j != id[j]; j = id[j])
				id[j] = id[id[j]];

			if (i == j)
				continue;

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

			cout << " " << p << " " << q << endl;
		}

		delete[] id;
		delete[] sz;
	}
}

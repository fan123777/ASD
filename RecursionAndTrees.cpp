#include "RecursionAndTrees.h"
#include "Tree.h"

namespace nsDataStructures
{
	namespace nsRecursionAndTrees
	{
		void main()
		{
			int res;
			res = factorial1(10);
			res = factorial2(10);
			res = puzzle(3);
			res = gcd(314159, 271828);
			res = F1(10);
			int N = 5;
			MyItem a[] = { { 3, 4 }, { 4, 5 }, { 7, 10 }, { 8, 11 }, { 9, 13 } };
			res = knap(17, a, N);
			res = knap1(17, a, N);
			testTree();
			int array[10] = { 1, 6, 9, 8, 3, 2, 1, 5, 7, 4 };
			Tree<int>* tree = max1(array, 0, 9);
			res = height(tree);
			show(tree, res);

		}

		int factorial1(int N)
		{
			if (N == 0)
				return 1;

			return N * factorial1(N - 1);
		}

		int factorial2(int N)
		{
			int i, t;

			for (t = 1, i = 1; i <= N; i++)
				t *= i;

			return t;
		}

		int puzzle(int N)
		{
			if (N == 1)
				return 1;

			if (N % 2 == 0)
				return puzzle(N / 2);
			else
				return puzzle(3 * N + 1);
		}

		int gcd(int m, int n)
		{
			if (n == 0)
				return m;
			return gcd(n, m % n);
		}

		int eval()
		{
			char *a; int i;
			int x = 0;
			while (a[i] == ' ')
				i++;
			if (a[i] == '+')
			{
				i++;
				return eval() + eval();
			}
			if (a[i] == '*')
			{
				i++;
				return eval() * eval();
			}
			while ((a[i] >= '0') && (a[i] <= '9'))
				x = 10 * x + (a[i++] - '0');
			return x;
		}

		void hanoi(int N, int d)
		{
			if (N = 0)
				return;
			hanoi(N - 1, -d);
			// shift(N, d);
			hanoi(N - 1, -d);
		}

		void rule(int l, int r, int h)
		{
			int m = (l + r) / 2;
			if (h > 0)
			{
				rule(l, m, h - 1);
				// mark(m, h);
				rule(m, r, h - 1);
			}
		}

		void rule1(int l, int r, int h)
		{
			for (int t = l, j = l; t <= h; j += j, t++)
			for (int i = 0; l + j + i <= r; i += j + j)
			{
				// mark(l + j + i, t);
			}
		}

		int F(int i)
		{
			if (i < 1)
				return 0;
			if (i == 1)
				return 1;
			return F(i - 1) + F(i - 2);
		}

		int F1(int i)
		{
			static int knownF[100];
			if (knownF[i] != 0)
				return knownF[i];
			int t = i;
			if (i < 0)
				return 0;
			if (i > 1)
				t = F1(i - 1) + F1(i - 2);
			return knownF[i] = t;
		}

		int knap(int cap, MyItem a[], int N)
		{
			int i, space, max, t;
			for (i = 0, max = 0; i < N; i++)
				if ((space = cap - a[i].size) >= 0)
					if ((t = knap(space, a, N) + a[i].val) > max)
						max = t;
			return max;
		}

		int knap1(int M, MyItem a[], int N)
		{
			static int maxKnown[100];
			int i, space, max, maxi = 0, t;
			if (maxKnown[M] != 0)
				return maxKnown[M];

			for (i = 0, max = 0; i < N; i++)
			if ((space = M - a[i].size) >= 0)
				if ((t = knap1(space, a, N) + a[i].val) >max)
				{
					max = t; maxi = i;
				}
			maxKnown[M] = max;
			return max;
		}

		void testTree()
		{
			Tree<int>* tree = new Tree<int>(5);
			tree->l = new Tree<int>(10);
			tree->r = new Tree<int>(2);

			tree->traverse(print);
			traverse(tree, print);
			traverse1(tree, print);

			int res = count(tree);
			res = height(tree);
			show(tree, res);

			delete tree->l;
			delete tree->r;
			delete tree;
		}
	}
}

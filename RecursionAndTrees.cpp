﻿#include "RecursionAndTrees.h"

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
	}
}

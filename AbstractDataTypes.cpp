#include "AbstractDataTypes.h"
#include <iostream>
#include "Point.h"
#include "Stack.h"
#include "UnionFind.h"
#include "Queue.h"
#include "Complex.h"
#include "Polynom.h"

using namespace std;

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		void main()
		{
			program2();
			program5(); // has some bug, debug it
			program6();
			const int N = 7;
			int a[N][2] = { { 1, 2 }, { 2, 3 }, { 1, 3 }, { 1, 5 }, { 4, 6 }, { 1, 3 }, { 6, 4 } };
			program10(N, a);
			program17();
			program20();
			program23(); // some error
		}

		void program2()
		{
			float d = 0.1;
			int i, cnt = 0, N = 100;
			Point *a = new Point[N];
			for (i = 0; i < N; i++)
				for (int j = i + 1; j < N; j++)
					if (a[i].distance(a[j]) < d)
						cnt++;

			cout << cnt << " pairs within " << d << endl;

			delete[] a;
		}

		template <class Item>
		void exch(Item &x, Item &y)
		{
			Item t = x;
			x = у;
			у = t;
		}

		void program5()
		{
			char* a = "598+46**7+*";
			int N = 11;
			nsArrayStack::Stack<int> save(N);
			for (int i = 0; i < N; i++)
			{
				if (a[i] == '+')
					save.push(save.pop() + save.pop());
				if (a[i] == '*') 
					save.push(save.pop() * save.pop());
				if ((a[i] >= '0') && (a[i] <= '9'))
					save.push(a[i]);
				while ((a[i] >= '0') && (a[i] <= '9'))
					save.push(10 * save.pop() + (a[i++] - '0'));
			}
			cout << save.pop() << endl;
		}

		void program6()
		{
			char* a = "5*(((9+8)*(4*6))+7))";
			int N = 20;
			nsArrayStack::Stack<char> ops(N);
			for (int i = 0; i < N; i++)
			{
				if (a[i] == ')')
					cout << ops.pop() << " ";
				if ((a[i] == '+') || (a[i] == '*'))
					ops.push(a[i]);
				if ((a[i] >= '0') && (a[i] <= '9'))
					cout << a[i] << " ";
			}
			cout << endl;
		}

		void program10(const int N, int a[][2])
		{
			int p, q, j;
			UnionFind info(N);

			for (j = 0; j < N; j++)
			{
				p = a[j][0];
				q = a[j][1];
				if (!info.find(p, q))
				{
					info.unite(p, q);
					cout << " " << p << " " << q << endl;
				}
			}
		}

		void program17()
		{
			int N = 2;
			cout << N << " complex roots of unity" << endl;
			for (int k = 0; k < N; k++)
			{
				float theta = 2.0 * 3.14159 * k / N;
				Complex t(cos(theta), sin(theta)), x = t;
				cout << k << ": " << t << " ";
				for (int j = 0; j < N - 1; j++)
					x *= t;
				cout << x << endl;
			}
		}

		void program20()
		{
			const int M = 4;

			int N = 10;
			nsListQueue::Queue<int> queues[M];

			for (int i = 0; i < N; i++, cout << endl)
			{
				int in = rand() % M, out = rand() % M;
				queues[in].put(i);
				cout << i << " in ";
				if (!queues[out].empty())
					cout << queues[out].get() << " out";
				cout << endl;
				for (int k = 0; k < M; k++, cout << endl)
				{
					nsListQueue::Queue<int> q = queues[k];
					cout << k << ": ";
					while (!q.empty())
						cout << q.get() << " ";
				}
			}
		}

		void program23()
		{
			int N = 5;
			float p = 1.1;
			cout << "Binomial coefficients" << endl;
			Polynom<int> x(1, 1), one(1, 0), t = x + one, y = t;
			for (int i = 0; i < N; i++)
			{
				y = y*t;
				// cout << y << endl;
			}
			cout << y.eval(p) << endl;
		}
	}
}

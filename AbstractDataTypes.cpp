#include "AbstractDataTypes.h"
#include <iostream>
#include "Point.h"
#include "Stack.h"
#include "UnionFind.h"
#include "Queue.h"

using namespace std;

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		void main()
		{
			// program2();
			// program5(); - has some bug, debug it
			// program6();

			const int N = 7;
			int a[N][2] = { { 1, 2 }, { 2, 3 }, { 1, 3 }, { 1, 5 }, { 4, 6 }, { 1, 3 }, { 6, 4 } };
			program10(N, a);
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
	}
}

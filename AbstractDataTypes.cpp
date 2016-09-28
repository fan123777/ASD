﻿#include "AbstractDataTypes.h"
#include "Point.h"
#include <iostream>
#include "Stack.h"

using namespace std;

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		void main()
		{
			// program2();
			// program5(); - has some bug, debug it
			program6();
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
	}
}

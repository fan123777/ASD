#include "AbstractDataTypes.h"
#include "Point.h"
#include <iostream>

using namespace std;

namespace nsDataStructures
{
	namespace nsAbstractDataTypes
	{
		void main()
		{
			program2();
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
	}
}

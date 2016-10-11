#include "ElementarySortingMethods.h"
#include <iostream>

using namespace std;

namespace nsSorting
{
	namespace nsElementarySortingMethods
	{
		void main()
		{
			int i, N = 10, sw = 1;
			int *a = new int[N];
			if (sw)
				for (i = 0; i < N; i++)
					a[i] = 1000 * (1.0*rand() / RAND_MAX);
			else
			{
				N = 0;
				while (cin >> a[N])
					N++;
			}
			sort(a, 0, N - 1);
			for (i = 0; i < N; i++)
				cout << a[i] << " ";
			cout << endl;

			delete[] a;
		}
	}
}

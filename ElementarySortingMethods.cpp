#include "ElementarySortingMethods.h"
#include <iostream>
#include "Array.h"

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
			// sort(a, 0, N - 1);
			// selection(a, 0, N - 1);
			// insertion(a, 0, N - 1);
			// bubble(a, 0, N - 1);
			shellsort(a, 0, N - 1);
			for (i = 0; i < N; i++)
				cout << a[i] << " ";
			cout << endl;

			delete[] a;

			program6();
		}

		void program6()
		{
			/*int N = 10, sw = 1;
			Item *a = new Item[N];
			if (sw)
				nsArray::rand(a, N);
			else
				nsArray::scan(a, N);
			nsArray::sort(a, 0, N - 1);
			nsArray::show(a, 0, N - 1);
			delete[] a;*/
		}
	}
}

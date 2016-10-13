#include "ElementarySortingMethods.h"
#include <iostream>
// #include "Item.h"
#include "Array.h"
// #include "SortList.h"

using namespace std;

namespace nsSorting
{
	namespace nsElementarySortingMethods
	{
		void main()
		{
			//testSort();
			program6();
			sortList();
		}

		void testSort()
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
		}

		void program6()
		{
			/*int N = 10, sw = 1;
			nsItem::Item *a = new nsItem::Item[N];
			if (sw)
				nsArray::rand(a, N);
			else
				nsArray::scan(a, N);
			nsArray::sort(a, 0, N - 1);
			nsArray::show(a, 0, N - 1);
			delete[] a;*/
		}

		void sortList()
		{
			// using namespace nsSortList;
			int i = 1;
			// showlist(sortlist(scanlist(i)));
		}

		void distcount(int a[], int l, int r)
		{
			const int M = 10;
			const int maxN = 20;
			int i, j, cnt[M];
			static int b[maxN];
			for (j = 0; j < M; j++)
				cnt[j] = 0;
			for (i = l; i <= r; i++)
				cnt[a[i] + 1]++;
			for (j = l; j < M; j++)
				cnt[j] += cnt[j - 1];
			for (i = l; i <= r; i++)
				b[cnt[a[i]]++] = a[i];
			for (i = l; i <= r; i++)
				a[i] = b[i - 1];
		}
	}
}

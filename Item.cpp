#include "Item.h"

using namespace std;

namespace nsSorting
{
	namespace nsElementarySortingMethods
	{
		namespace nsRecordItem
		{
			// Программа 6.13.Реализация типа данных записей
			const int maxN = 20;
			static record data[maxN];
			static int cnt = 0;

			void show(const Item& x)
			{
				cout << x.r->name << " " << x.r->num << endl;
			}

			void scan(Item& x)
			{
				x.r = &data[cnt++];
				cin >> x.r->name >> x.r->num;
			}
		}
	}
}

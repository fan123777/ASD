#include "Item.h"

using namespace std;

namespace nsSorting
{
	namespace nsElementarySortingMethods
	{
		namespace nsItem
		{
			namespace nsCharItem
			{
				// Программа 6.11.Реализация типов данных для строковых элементов
				typedef struct { char *str; } StrItem;

				static char buf[100000];
				static int cnt = 0;

				int operator<(const StrItem& a, const StrItem& b)
				{
					return strcmp(a.str, b.str) < 0;
				}

				void show(const StrItem& x)
				{
					cout << x.str << " ";
				}

				void scan(StrItem& x)
				{
					cin >> (x.str = &buf[cnt]);
					cnt += strlen(x.str) + 1;
				}

				struct intWrapper
				{
					int item;
					intWrapper(int i = 0)
					{
						item = i;
					}
					operator int() const
					{
						return item;
					}
				};

				typedef intWrapper Index;

				/*int operator<(const Index& i, const Index& j)
				{
				return data[i] < data[j];
				}*/
			}

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
}

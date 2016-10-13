#pragma once

namespace nsSorting
{
	namespace nsElementarySortingMethods
	{
		namespace nsArray
		{
			// Программа 6.7.Интерфейс для данных типа массив
			/*template <class Item>
			void rand(Item a[], int N);
			template <class Item>
			void scan(Item a[], int &N);
			template <class Item>
			void show(Item a[], int l, int r);
			template <class Item>
			void sort(Item a[], int l, int r);*/

			// Программа 6.8.Реализация типа данных массива
			template <class Item>
			void rand(Item a[], int N)
			{
				for (int i = 0; i < N; i++)
					nsItem::rand(a[i]);
			}

			template <class Item>
			void scan(Item a[], int& N)
			{
				for (int i = 0; i < N; i++)
					nsItem::scan(a[i]);
			}

			template <class Item>
			void show(Item a[], int l, int r)
			{
				for (int i = l; i <= r;i++)
					nsItem::show(a[i]);
				std::cout << std::endl;
			}

			// shellsort
			template <class Item>
			void sort(Item a[], int l, int r)
			{
				int h;
				for (h = 1; h <= (r - l) / 9; h = 3 * h + 1);
				for (; h > 0; h /= 3)
				for (int i = l + h; i <= r; i++)
				{
					int j = i;
					Item v = a[i];
					while (j >= l + h && v < a[j - h])
					{
						a[j] = a[j - h];
						j -= h;
					}
					a[j] = v;
				}
			}
		}
	}
}

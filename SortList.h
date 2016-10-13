#pragma once

namespace nsSorting
{
	namespace nsElementarySortingMethods
	{
		namespace nsSortList
		{
			// Программа 6.15.Определение интерфейса для типа связного списка
			typedef int Item;

			struct node
			{
				Item item;
				node* next;

				node(Item x)
				{
					item = x;
					next = 0;
				}
			};

			typedef node *link;
			link randlist(int);
			link scanlist(int&);
			void showlist(link);
			link sortlist(link);
			
			// Программа 6.16.Сортировка выбором связного списка
			link findmax(link);

			link listselection(link h)
			{
				node dummy(0);
				link head = &dummy, out = 0;
				head->next = h;
				while (head->next != 0)
				{
					link max = findmax(head), t = max->next;
					max->next = t->next;
					t->next = out; out = t;
				}
				return out;
			}
		}
	}
}

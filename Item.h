#pragma once
#include <iostream>

namespace nsSorting
{
	namespace nsElementarySortingMethods
	{
		namespace nsItem
		{
			// Программа 6.9. Пример интерфейса для данных типа Item 
			typedef struct record { int key; float info; } Item;
			int operator<(const Item&, const Item&);
			// int scan(Item&);
			// void rand(Item&);
			// void show(const Item&);

			// Программа 6.10.Пример реализации типа данных
			int operator<(const Item& A, const Item& B)
			{
				return A.key < B.key;
			}

			void scan(Item& x)
			{
				std::cin >> x.key >> x.info;
			}

			void rand(Item& x)
			{
				x.key = 1000 * (1.0*std::rand() / RAND_MAX);
				x.info * 1.0*std::rand() / RAND_MAX;
			}
			
			void show(const Item& x)
			{
				std::cout << x.key << " " << x.info << std::endl;
			}

			namespace nsRecordItem
			{
				// Программа 6.12.Интерфейс типа данных для элементов типа запись
				struct record { char name[30]; int num; };
				typedef struct { record *r; } Item;
				int operator<(const Item& , const Item&);
				void rand(Item&);
				void show(const Item&);
				void scan(Item&);
			}
		}
	}
}

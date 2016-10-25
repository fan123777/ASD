#pragma once

#include <stdlib.h> 
#include <iostream> 

static int maxKey = 1000;
typedef int Key;


namespace nsSearch
{
	namespace nsCharacterTablesAndBinarySearchTrees
	{
		namespace nsSearchItem
		{
			// Программа 12.1 Пример реализации АТД элемента
			class Item
			{
			private:
				Key keyval;
				float info;
			public:
				Item()
				{
					keyval = maxKey;
				}

				Key key()
				{
					return keyval;
				}

				int null()
				{
					return keyval = maxKey;
				}

				void rand()
				{
					keyval = 1000 * std::rand() / RAND_MAX;
					info = 1.0*std::rand() / RAND_MAX;
				}

				void scan(std::istream& is = std::cin)
				{
					is >> keyval >> info;
				}

				void show(std::ostream& os = std::cout)
				{
					os << keyval << " " << info << std::endl;
				}
			};

			std::ostream& operator<<(std::ostream& os, Item& x)
			{
				x.show(os);
				return os;
			}
		}
	}
}
